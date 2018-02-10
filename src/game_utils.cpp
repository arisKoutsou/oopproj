// game_utils.cpp --- 
// 
// Filename: game_utils.cpp
// Author: George Liontos
// Created: Sun Jan 28 02:34:01 2018 (+0200)

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>

#include "game_utils.h"
#include "grid/Grid.h"
#include "market/Market.h"
#include "livings/Hero.h"
#include "items/Weapon.h"
#include "items/Armor.h"
#include "items/Potion.h"
#include "spells/FireSpell.h"
#include "spells/IceSpell.h"
#include "spells/LightningSpell.h"
#include "exceptions/heroExceptions.h"
#include "livings/heroes/Warrior.h"
#include "livings/heroes/Sorcerer.h"
#include "livings/heroes/Paladin.h"
#include "livings/Monster.h"
#include "livings/monsters/Dragon.h"
#include "livings/monsters/Spirit.h"
#include "livings/monsters/Exoskeleton.h"

using namespace std;

static const double battleProbability = 0.1;
static const Random rng;
static bool quitGame = false;
static string buffer;
static vector<Hero*> heroes;
static vector<string> names;
static vector<string> weapons;
static vector<string> armors;
static vector<string> potions;
static vector<string> spells;
static list<Monster*> monsters;
static ifstream map;
static Grid* gameGrid;

void initGrid(void) {  
  vector<string> tokens;
  skipCommentsAndWhitespace(map);
  tokenize(tokens);
  // REALLY??? stoi is C++11 :(
  int rows = atoi(tokens[0].c_str());
  int columns = atoi(tokens[1].c_str());
  skipCommentsAndWhitespace(map);
  tokens.clear();
  tokenize(tokens);
  while (map.eof() == false) {
    getline(map, buffer);
    tokenize(tokens);
  }
  bool* tileInfo = new bool[rows*columns*2];
  size_t j = 0U;
  for (size_t i = 0U; i < tokens.size();) {
    tileInfo[j++] = (tokens[i] == "true") ? true : false;
    tileInfo[j++] = (tokens[i+1] == "true") ? true : false;
    i += (tokens[i+2] == "false") ? 3 : 4;
  }
  gameGrid = new Grid(rows, columns, tileInfo);
  ssize_t row = 0U;
  ssize_t col = 0U;
  for (size_t i = 2U; i < tokens.size(); ++col) {
    if (col == columns) { ++row, col = 0U; }
    if (tokens[i] == "false") { i += 3U; continue; }
    int cap = atoi(tokens[i+1].c_str());
    Market* market = new Market(cap);
    fillMarket(market);
    gameGrid->addMarket(row, col, market);
    i += 4U;
  }
  delete[] tileInfo;
}

void fillMarketItems(Market* market, int size) {
  for (int i = 0; i != size; ++i) {
    int kind = rng.fromMintoMax(0, 2);
    switch (kind) {
    case 0: {
      string name = weapons[rng.fromMintoMax(0, weapons.size() - 1)];
      Weapon* newWeapon = new Weapon(name);
      market->addItem(newWeapon);
      break;
    }
    case 1: {
      string name = armors[rng.fromMintoMax(0, armors.size() - 1)];
      Armor* newArmor = new Armor(name);
      market->addItem(newArmor);
      break;
    }
    case 2: {
      string name = potions[rng.fromMintoMax(0, potions.size() - 1)];
      Potion* newPotion = new Potion(name);
      market->addItem(newPotion);
      break;
    }
    }
  }
}

void fillMarketSpells(Market* market, int size) {
  for (int i = 0; i != size; ++i) {
    int kind = rng.fromMintoMax(0, 2);
    string name = spells[rng.fromMintoMax(0, spells.size() - 1)];
    switch (kind) {
    case 0: {
      FireSpell* newFireSpell = new FireSpell(name);
      market->addSpell(newFireSpell);
      break;
    }
    case 1: {
      IceSpell* newIceSpell = new IceSpell(name);
      market->addSpell(newIceSpell);
      break;
    }
    case 2: {
      LightningSpell* newLightningSpell = new LightningSpell(name);
      market->addSpell(newLightningSpell);
      break;
    }
    }
  }
}

void fillMarket(Market* market) {
  fillMarketItems(market, market->getMaxCapacity()/2);
  fillMarketSpells(market, market->getMaxCapacity() -
		   market->getMaxCapacity()/2);
}

bool isCommentOrWhitespace(const string& str) {
  if (str[0] == '#') return true;
  for (size_t i = 0U; i != str.length(); ++i) {
    if (!isspace(str[i])) return false;
  }
  return true;
}

void skipCommentsAndWhitespace(ifstream& stream) {
  while (stream.eof() == false) {
    getline(stream, buffer);
    if (isCommentOrWhitespace(buffer)) continue;
    break;
  }
}

void tokenize(vector<string>& tokens) {
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

void handleBasicCase(Hero* currentHero) {
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

void handleMoveCase(Hero* currentHero) {
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

void handleQuitCase(void) {
  string answer;
  do {
    cout << "Do you you really want to quit?" << endl;
    cin >> answer;        
  } while (answer != "yes" && answer != "no");
  if (answer == "yes") {
    quitGame = true;
  }
}

void handleBattleCase(void) {
  createMonsters();
  int rounds = 1;
  while (true) {    
    int livingsPlayed = 0;
    size_t heroIndex = 0U;
    bool heroesTurn = true;
    cout << "ROUND " << rounds << endl << endl;
    while (monsters.size() != 0 && livingsPlayed != (monsters.size() + heroesAlive())) {
      if (heroesTurn) {
	while (heroes[heroIndex]->getHealthPower() == 0) ++heroIndex;
        heroes[heroIndex]->battle(monsters);
	heroes[heroIndex]->nextRound();
	heroIndex = (heroIndex + 1) % heroes.size();
	heroesTurn = false;        
      } else {
	// TODO (George): I should modify the monster class in order
	// to check if the monster has been nerfed from a spell attack
	size_t monsterIndex = rng.fromMintoMax(0, monsters.size() - 1);
        list<Monster*> :: const_iterator it = monsters.begin();
        while (monsterIndex-- != 0) ++it;
        size_t heroToAttackIndex;
        do {
          heroToAttackIndex = rng.fromMintoMax(0, heroes.size() - 1);
        } while (heroes[heroToAttackIndex]->getHealthPower() == 0);
        (*it)->attack(heroes[heroToAttackIndex]);
        heroesTurn = true;
      }
      ++livingsPlayed;
    }
    if (heroesWon()) {
      claimRewards();
      break;
    } else if (monstersWon()) {
      receivePenalty();
      break;
    }
    regenerateStats();
    ++rounds;
  }
  restoreHeroes();
  cleanupMonsters();
}

// INCOMPLETE (George)
void createMonsters(void) {
  // TODO (George): Find a way so the monsters that get spawned
  // have the proper stats based on the heroes level (or average level)
  int numberOfMonsters = rng.fromMintoMax(MIN_MONSTERS, MAX_MONSTERS);
  int heroY = heroes[0]->getPosition().getY();
  int heroX = heroes[0]->getPosition().getX();
  for (size_t i = 0U; i != numberOfMonsters; ++i) {
    int kind = rng.fromMintoMax(0, 2);
    string name = names[rng.fromMintoMax(0, names.size() - 1)];
    switch (kind) {
    case 0: {
      Dragon* dragon = new Dragon(gameGrid, heroY, heroX, name);
      monsters.push_back(dragon);      
      break;
    }
    case 1: {
      Exoskeleton* ex = new Exoskeleton(gameGrid, heroY, heroX, name);
      monsters.push_back(ex);
      break;
    }
    case 2: {
      Spirit* spirit = new Spirit(gameGrid, heroY, heroX, name);
      monsters.push_back(spirit);
      break;
    }
    }
  }
}

int heroesAlive(void) {
  int alive = 0;
  for (size_t i = 0U; i != heroes.size(); ++i) {
    if (heroes[i]->getHealthPower() != 0) ++alive;
  }
  return alive;
}

bool heroesWon(void) {
  return (monsters.size() == 0);
}

bool monstersWon(void) {
  size_t dead = 0U;
  for (size_t i = 0U; i != heroes.size(); ++i) {
    if (heroes[i]->getHealthPower() == 0) ++dead;
  }
  return (dead == heroes.size()) ? true : false;
}

void claimRewards(void) {
  for (size_t i = 0U; i != heroes.size(); ++i) {
    int monstersKilled = heroes[i]->getMonstersKilled();
    if (monstersKilled != 0) {
      // TODO (George): Find a formula for getting the reward money
      int experienceToClaim = heroes[i]->getLevel()*0.2*monstersKilled + 50*monstersKilled;

      heroes[i]->setExperience(heroes[i]->getExperience() + experienceToClaim);

      if (heroes[i]->getExperience() > heroes[i]->getExperienceMilestone()) {
	// Hero exceeded the milestone. He needs to level up.
	heroes[i]->levelUp();		// Level up the Hero. Deserves it.
	heroes[i]->nextMilestone();	// Set a new milestone.
      }

      int moneyToClaim = heroes[i]->getLevel()*0.1*monstersKilled + 100*monstersKilled;
      heroes[i]->setMoney(heroes[i]->getMoney() + moneyToClaim);

    }
  }
}

void receivePenalty(void) {
  for (size_t i = 0U; i != heroes.size(); ++i) {
    heroes[i]->setMoney(heroes[i]->getMoney()/2);
  }
}

void restoreHeroes(void) {
  for (size_t i = 0U; i != heroes.size(); ++i) {
    heroes[i]->resetBattleStats();
    if (heroes[i]->getHealthPower() == 0) {
      heroes[i]->respawn();
    }
  }  
}

void cleanupMonsters(void) {
  while (monsters.empty() == false) {
    delete monsters.front();
    monsters.pop_front();
  }
}

void regenerateStats(void) {
  for (size_t i = 0U; i != heroes.size(); ++i) {
    if (heroes[i]->getHealthPower() != 0) {
      int health = heroes[i]->getHealthPower();
      int mana = heroes[i]->getMagicPower();
      heroes[i]->setHealthPower(health + health*0.3);
      if (heroes[i]->getHealthPower() > heroes[i]->getMaxHealthPower()) {
	heroes[i]->setHealthPower(heroes[i]->getMaxHealthPower());
      }
      if (mana == 0) {
	heroes[i]->setMagicPower(100);
      } else {
	heroes[i]->setMagicPower(mana + mana*0.4);
	if (heroes[i]->getMagicPower() > heroes[i]->getMaxMagicPower()) {
	  heroes[i]->setMagicPower(heroes[i]->getMaxMagicPower());
	}
      }
    }
  }
  list<Monster*> :: const_iterator it = monsters.begin();
  for ( ; it != monsters.end(); ++it) {
    int health = (*it)->getHealthPower();
    (*it)->setHealthPower(health + health*0.3);
    if ((*it)->getHealthPower() > (*it)->getMaxHealthPower()) {
      (*it)->setHealthPower((*it)->getMaxHealthPower());
    }
  }
}

void createHeroes(int numberOfHeroes) {
  for (int i = 0; i != numberOfHeroes; ++i) {
    cout << "Please enter a class for hero " << i + 1
	 << " (possible classes are Warrior, Sorcerer, Paladin): ";
    string heroClass;
    cin >> heroClass;

    if (!(heroClass == "Warrior"
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
    cout << endl;
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

void readData(int argc, char* argv[]) {
  ifstream inputStream;
  for (size_t i = 1U; i != argc; ++i) {
    inputStream.open(argv[i]);
    if (strstr(argv[i], "names.txt")) {
      readSpecificData(inputStream, names);
    } else if (strstr(argv[i], "armors.txt")) {
      readSpecificData(inputStream, armors);
    } else if (strstr(argv[i], "weapons.txt")) {
      readSpecificData(inputStream, weapons);
    } else if (strstr(argv[i], "potions.txt")) {
      readSpecificData(inputStream, potions);
    } else if (strstr(argv[i], "spells.txt")) {
      readSpecificData(inputStream, spells);
    }
    inputStream.close();
  }
}

void readSpecificData(ifstream& stream, vector<string>& data) {
  while (stream.eof() == false) {
    getline(stream, buffer);
    data.push_back(buffer);
  }
}

void checkArgumentsAndSetMap(int argc, char* argv[]) {
  if (argc < 7) {
    cerr << "Too few arguments! You should provide the program with:"
	 << endl << "map.txt, names.txt, weapons.txt, spells.txt, "
	 << "potions.txt, and armors.txt" << endl;
    exit(EXIT_FAILURE);
  }
  for (size_t i = 1U; i != argc; ++i) {
    if (strstr(argv[i], "map.txt")) {
      map.open(argv[i]);
      break;
    }
  }
}

int getNumberOfHeroes(void) {
  int numberOfHeroes = -1;
  while (numberOfHeroes < 1 || numberOfHeroes > 3) {
    cout << "Please enter the number of heroes you want to have "
	 << "(min: 1, max: 3): ";
    cin >> numberOfHeroes;
  }
  return numberOfHeroes;
}

void cleanupResources(void) {
  delete gameGrid;
  map.close();
}

void run(int argc, char* argv[]) {
  checkArgumentsAndSetMap(argc, argv);
  readData(argc, argv);
  int numberOfHeroes = getNumberOfHeroes();
  initGrid();
  createHeroes(numberOfHeroes);
  int heroTurn = 0;
  bool battled = false;
  while (quitGame == false) {
    Hero* currentHero = heroes[heroTurn];
    heroTurn = (heroTurn + 1) % numberOfHeroes;
    cout << endl << "Hero Playing: "
	 << currentHero->getName() << endl << endl;
    if (!battled && currentHero->getTile().isQualifiedForBattle(numberOfHeroes)) {
      if (rng.boolean(battleProbability)) {
    	handleBattleCase();
	battled = true;
	continue;
      }      
    }
    handleBasicCase(currentHero);
    battled = false;
  }
  cleanupResources();
}
