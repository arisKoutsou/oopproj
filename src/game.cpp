#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cctype>
#include <string>

#include "livings/Hero.h"
#include "grid/Grid.h"
#include "random/Random.h"
#include "items/Weapon.h"
#include "livings/Monster.h"
#include "livings/monsters/Dragon.h"
#include "livings/monsters/Spirit.h"
#include "livings/monsters/Exoskeleton.h"
#include "livings/heroes/Warrior.h"
#include "livings/heroes/Sorcerer.h"
#include "livings/heroes/Paladin.h"
#include "exceptions/heroExceptions.h"
#include "market/Market.h"

using namespace std;

static int numberOfHeroes;
static vector<Hero*> heroes;
static list<Monster*> monsters;
static const Random rng;
static const double battleProbability = 0.6;
static Grid* gameGrid;
static int rows = 10;
static int columns = 15;
static bool quitGame = false;
static string buffer;

inline void initGrid(void) {  
  bool* randomTileInfo = new bool[rows*columns*2];
  for (int i = 0; i != rows*columns*2; i += 2) {
    randomTileInfo[i] = rng.boolean(0.1);
    randomTileInfo[i+1] = !randomTileInfo[i];
  }
  gameGrid = new Grid(rows, columns, randomTileInfo);
  delete[] randomTileInfo;
}

inline bool isCommentOrWhitespace(const string& str) {
  if (str[0] == '#') return true;
  for (size_t i = 0U; i != str.length(); ++i) {
    if (!isspace(str[i])) return false;
  }
  return true;
}

inline void skipCommentsAndWhitespace(ifstream& stream) {
  while (stream.eof() == false) {
    getline(stream, buffer);
    if (isCommentOrWhitespace(buffer)) continue;
    break;
  }
}

inline void tokenize(vector<string>& tokens) {
  string token;
  size_t pos = 0U;
  // Finding the position of the delimiter (',')
  // string :: npos is just the greatest value of size_t
  while ((pos = buffer.find(',')) != string :: npos) {
    token = buffer.substr(0, pos);
    tokens.push_back(token);
    buffer.erase(0, pos + 1);    
  }  
}

inline void initGrid(ifstream& stream) {  
  vector<string> tokens;
  skipCommentsAndWhitespace(stream);
  tokenize(tokens);
  // REALLY??? stoi is C++11 :(
  rows = atoi(tokens[0].c_str());
  columns = atoi(tokens[1].c_str());
  skipCommentsAndWhitespace(stream);
  tokens.clear();
  while (stream.eof() == false) {
    tokenize(tokens);
    getline(stream, buffer);
  }
  bool* tileInfo = new bool[rows*columns*2];
  size_t j = 0U;
  for (size_t i = 0U; i != tokens.size();) {
    tileInfo[j++] = (tokens[i] == "true") ? true : false;
    tileInfo[j++] = (tokens[i+1] == "true") ? true : false;
    if (tokens[i+2] == "false") i += 3;
    else i += 4;
  }
  gameGrid = new Grid(rows, columns, tileInfo);
  size_t row = 0U;
  size_t col = 0U;
  for (size_t i = 2U; i < tokens.size(); i += 3U, ++col) {
    if (col == columns) { ++row, col = 0; }
    if (tokens[i] == "false") continue;
    int cap = atoi(tokens[i+1].c_str());
    Market* market = new Market(cap);
    gameGrid->addMarket(row, col, market);
  }
  delete[] tileInfo;
}

inline void createHeroes(int numberOfHeroes) {
  for (int i = 0; i != numberOfHeroes; ++i) {
    cout << "Please enter a class for hero " << i + 1
	 << " (possible classes are Warrior, Sorcerer, Paladin): ";
    string heroClass;
    cin >> heroClass;

    if (! (heroClass == "Warrior"
         || heroClass == "Paladin"
         || heroClass == "Sorcerer")
    ) {
    	cout << "That's not a valid class!" << endl;
	    --i;
	    continue;
    }

    cout << "Please enter a name for your hero: ";
	string name;
	cin >> name;

	Hero* hero;
    if (heroClass == "Warrior") {
      hero = new Warrior(gameGrid, name);
    } else if (heroClass == "Sorcerer") {
      hero = new Sorcerer(gameGrid, name);
    } else if (heroClass == "Paladin") {
      hero = new Paladin(gameGrid, name);
    }

    heroes.push_back(hero);
  }
}

inline void handleMoveCase(Hero* currentHero) {
  bool moved = false;
  while (!moved) {
    cout << "Please enter the direction you want to move "
	 << "(possible directions are up, down, left, right): ";
    string answer;
    cin >> answer;
    Hero :: directions direction;
    if (answer == "up") direction = Hero :: UP;
    else if (answer == "down") direction = Hero :: DOWN;
    else if (answer == "left") direction = Hero :: LEFT;
    else if (answer == "right") direction = Hero :: RIGHT;
    try {
      currentHero->move(direction);
      moved = true;
    }
    catch (HeroMoveException& e) {
      cout << e.what() << endl;
      moved = false;
    }
  }
  if (currentHero->getTile().hasMarket()) {
    string answer;
    do {
      cout << "It seems that you found a market... Do you want to enter?(Y/n)"
	   << endl;
      cin >> answer;
    } while (answer != "Y" && answer != "n" && answer != "y");
    if (answer == "Y" || answer == "y") {
      currentHero->enterMarket(currentHero->getTile().getMarket());
    }
  }
}

inline void handleQuitCase(void) {
  string answer;
  do {
    cout << "Do you you really want to quit?" << endl;
    cin >> answer;        
  } while (answer != "yes" && answer != "no");
  if (answer == "yes") {
    quitGame = true;
  }
}

inline void handleBasicCase(Hero* currentHero) {
  int selection;  
  currentHero->getGameMenu().displayMenu();
  while ((selection = currentHero->getGameMenu().getSelection())) {
    switch (selection) {
    case 1: currentHero->displayMap(); break;
    case 2: currentHero->printStats(); break;
    case 3: currentHero->checkInventory(); return;
    case 4: handleMoveCase(currentHero); return;
    case 5: handleQuitCase(); if (quitGame) return; break;
    default: break;
    }
    currentHero->getGameMenu().clearMenu();
    currentHero->getGameMenu().displayMenu();
  }
}

inline void handleBattleCase() {
  // 
}

int main(int argc, char* argv[]) {  
  // initGrid();
  ifstream map(argv[1]);
  initGrid(map);
  while (numberOfHeroes < 1 || numberOfHeroes > 3) {
	cout << "Please enter the number of heroes you want to have "
		 << "(min: 1, max: 3): ";

	cin >> numberOfHeroes;
  }

  createHeroes(numberOfHeroes);

  Market* market = new Market();
  Weapon* sword = new Weapon("Excalibur");
  market->addItem(sword);
  gameGrid->addMarket(1, 0, market);

  int heroTurn = 0;

  while (quitGame == false) {
    Hero* currentHero = heroes[heroTurn];
    heroTurn = (heroTurn + 1) % numberOfHeroes;
    cout << endl << "Hero Playing: "
	 << currentHero->getName() << endl << endl;
    handleBasicCase(currentHero);
    // if (currentHero->getTile().isQualifiedForBattle(numberOfHeroes)) {
    //   if (rng.boolean(battleProbability)) {
    // 	handleBattleCase();
    //   }      
    // } else {
    // }    
  }

  delete gameGrid;
  map.close();
  return EXIT_SUCCESS;
}
