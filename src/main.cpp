#include <iostream>
#include <cstdlib>
#include <vector>
#include "livings/Hero.h"
#include "grid/Grid.h"
#include "random/Random.h"
#include "items/Weapon.h"
#include "livings/heroes/Warrior.h"
#include "livings/heroes/Sorcerer.h"
#include "livings/heroes/Paladin.h"
#include "exceptions/heroExceptions.h"
#include "market/Market.h"

using namespace std;

static vector<Hero*> heroes;
static Random rng;
static Grid* gameGrid;
static int rows = 10;
static int columns = 15;
static bool quitGame = false;

inline void initGrid(void) {  
  bool* randomTileInfo = new bool[rows*columns*2];
  for (int i = 0; i != rows*columns*2; i += 2) {
    randomTileInfo[i] = rng.boolean(0.1);
    randomTileInfo[i+1] = !randomTileInfo[i];
  }
  gameGrid = new Grid(rows, columns, randomTileInfo);
  delete[] randomTileInfo;
}

inline void createHeroes(int numberOfHeroes) {
  for (int i = 0; i != numberOfHeroes; ++i) {
    cout << "Please enter a class for hero " << i + 1
	 << " (possible classes are Warrior, Sorcerer, Paladin): ";
    string heroClass;
    cin >> heroClass;
    if (heroClass == "Warrior") {
      cout << "Please enter a name for your hero: ";
      string name;
      cin >> name;
      Warrior* warrior = new Warrior(gameGrid, name);
      heroes.push_back(warrior);
    } else if (heroClass == "Sorcerer") {
      cout << "Please enter a name for your hero: ";
      string name;
      cin >> name;
      Sorcerer* sorcerer = new Sorcerer(gameGrid, name);
      heroes.push_back(sorcerer);
    } else if (heroClass == "Paladin") {
      cout << "Please enter a name for your hero: ";
      string name;
      cin >> name;
      Paladin* paladin = new Paladin(gameGrid, name);
      heroes.push_back(paladin);
    } else {
      cout << "That's not a valid class!" << endl;
      --i;
    }
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
      cout << "It seems that you found a market... Do you want to enter?"
	   << endl;
      cin >> answer;
    } while (answer != "yes" && answer != "no");
    if (answer == "yes") {
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

void handleBattleCase(Hero* currentHero) {
  //  
}

int main(void) {
  initGrid();
  int numberOfHeroes;
  cout << "Please enter the number of heroes you want to have "
       << "(min: 1, max: 3): ";
  cin >> numberOfHeroes;
  createHeroes(numberOfHeroes);
  Market* market = new Market();
  Weapon* sword = new Weapon("Excalibur");
  market->addItem(sword);
  gameGrid->addMarket(1, 0, market);
  int heroTurn = 0;
  while (quitGame == false) {
    Hero* currentHero = heroes[heroTurn];
    heroTurn = (heroTurn + 1) % numberOfHeroes;
    cout << endl << "Hero Playing: " << currentHero->getName() << endl << endl;
    if (currentHero->isInBattle()) {
      handleBattleCase(currentHero);
    } else {
      handleBasicCase(currentHero);
    }
  }
  delete gameGrid;
  return EXIT_SUCCESS;
}
