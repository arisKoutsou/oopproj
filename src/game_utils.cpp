// game_utils.cpp --- 
// 
// Filename: game_utils.cpp
// Author: George Liontos
// Created: Sun Jan 28 02:34:01 2018 (+0200)

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <limits>

#include "game_utils.h"
#include "grid/Grid.h"
#include "menu/AllMenus.h"
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

bool quitGame = false;

static const double battleProbability = 0.9;
static const Random rng;
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

void generateMap() {
  cout << endl;
  cout << "A Map/Grid is a 2d array of Tiles." << endl;
  cout << "with <rows> rows and <cols> columns." << endl;
  cout << "Each Tile can have a probability to have a Market (m)." << endl;
  cout << "A probability to be non Accessible (x)." << endl;
  cout << "And a probabilty to be common (c)." << endl;
  cout << "Probability is a number in the interval [0, 1]." << endl;
  cout << "Please enter dimensions and probabilities in the following order:" << endl;
  cout << "<rows> <cols> <m> <x> <c>\t\t(i.e : 4  5  0.1  0.3  0.03 )" << endl;
  cout << endl;
  cout << "> ";

  int rows, columns;
  double pMarket, pNonAccessible, pCommon;
  cin >> rows >> columns
      >> pMarket >> pNonAccessible >> pCommon;

  Random rng;
  ofstream newMap("../input/map.txt");
  newMap << "# Map goes as follows: Each line has information about a tile" << endl
	 << "# First value (true, false) is about nonAccessible" << endl
	 << "# Second value (true, false) is about common" << endl
	 << "# Third value (true, false) is about market. If it's true "
	 << "then an in is given which is the capacity of the market" << endl
	 << "# First line has the dimensions of the grid (row, col)" << endl
	 << "# The delimiter is ','" << endl << endl;
  newMap << rows << "," << columns << "," << endl << endl;
  newMap << "false,false,false," << endl; /* That's the first tile. That's where our heroes spawn */
  for (size_t i = 2U; i != rows*columns*2; i += 2) {
    bool non_accessible = rng.boolean(pNonAccessible);
    bool common = rng.boolean(pCommon);
    bool market = rng.boolean(pMarket);
    if (non_accessible) {
      newMap << "true,";
      common = false;
      market = false;
    } else newMap << "false,";
    if (common) {
      newMap << "true,";
      market = false;
    } else newMap << "false,";
    if (market) {
      newMap << "true,";
      int cap = rng.fromMintoMax(5, 15);
      newMap << cap << ",";
    } else newMap << "false,";
    newMap << endl;
  }
  newMap.close();

  cout << endl << "Map generated !" << endl;

  string answer;
  while (answer != "Y" && answer != "y") {
    cout << endl << "Exit to Main Menu?(Y/n) : ";
    cin >> answer;
  }
}

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
  currentHero->getGameMenu().clearMenu();
  currentHero->getGameMenu().displayMenu();
  while ((selection = currentHero->getGameMenu().getSelection())) {   
    currentHero->getGameMenu().clearMenu();
    switch (selection) {
    case 1: currentHero->displayMap(); break;
    case 2: currentHero->printStats(); break;
    case 3: currentHero->checkInventory(); return;
    case 4: handleMoveCase(currentHero); return;
    case 5: handleQuitCase(); currentHero->getGameMenu().clearMenu();
	    if (quitGame) return; break;
    default: break;
    }    
    currentHero->getGameMenu().displayMenu();
  }
}

void handleMoveCase(Hero* currentHero) {
  bool moved = false;
  while (!moved) {
    cout << endl
	 << "Please enter the direction you want to move "
	 << "(possible directions are up, down, left, right)"
	 << endl << endl << "> ";
    string answer;
    cin >> answer;
    Hero :: directions direction;
    if (answer == "up") direction = Hero :: UP;
    else if (answer == "down") direction = Hero :: DOWN;
    else if (answer == "left") direction = Hero :: LEFT;
    else if (answer == "right") direction = Hero :: RIGHT;
    else direction = Hero :: UNKNOWN;
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
      cout << "It seems that you found a market... Do you want to enter?(Y|n)"
	   << endl << endl << "> ";
      cin >> answer;
      transform(answer.begin(), answer.end(), answer.begin(), :: tolower);
    } while (answer != "y" && answer != "n");
    if (answer == "y") {
      currentHero->enterMarket(currentHero->getTile().getMarket());
    }
  }
}

void handleQuitCase(void) {
  string answer;

  while (true) {
    cout << endl
	 << "Do you you really want to go to the main menu? (Y|n)" << endl
	 << "(If you answer Y the current session will be terminated)"
	 << endl << endl;
    cout << "> ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), :: tolower);
    if (answer == "y") {
      quitGame = true;
      break;
    } else if (answer == "n") {
      cout << endl;
      break;
    }
  }
}

void handleBattleCase(void) {
  createMonsters();
  int rounds = 1;
  while (true) {    
    int livingsPlayed = 0;
    size_t heroIndex = 0U;
    bool heroesTurn = true;
    cout << endl << "ROUND " << rounds;
    while (monsters.size() != 0 && livingsPlayed != (monsters.size() + heroesAlive())) {
      if (heroesTurn) {
	while (heroes[heroIndex]->getHealthPower() == 0) ++heroIndex;
        heroes[heroIndex]->battle(monsters);
	if (quitGame) return;
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
    updatePotionsAndNerfs();
    ++rounds;
  }
  restoreHeroes();
  cleanupMonsters();
}

void createMonsters(void) {
  int numberOfMonsters = rng.fromMintoMax(MIN_MONSTERS, MAX_MONSTERS);
  int heroY = heroes[0]->getPosition().getY();
  int heroX = heroes[0]->getPosition().getX();
  int averageLevel;
  for (int i = 0; i != heroes.size(); ++i) {
    averageLevel += heroes[i]->getLevel();
  }
  averageLevel /= heroes.size();
  int healthPower = 500 + 50*averageLevel;
  int minDamage = 10 + 15*averageLevel;
  int maxDamage = 20 + 15*averageLevel;
  double armor = 0.1 + 0.2*averageLevel;
  double dodge = 0.1 + 0.15*averageLevel;
  for (size_t i = 0U; i != numberOfMonsters; ++i) {
    int kind = rng.fromMintoMax(0, 2);
    string name = names[rng.fromMintoMax(0, names.size() - 1)];
    switch (kind) {
    case 0: {
      double damageBonus = 5 + 5*averageLevel;
      Dragon* dragon = new Dragon(gameGrid, heroY, heroX, name,
				  healthPower, minDamage, maxDamage,
				  armor, dodge, damageBonus);
      monsters.push_back(dragon);
      break;
    }
    case 1: {
      double armorBonus = 0.15 + 0.1*averageLevel;
      Exoskeleton* ex = new Exoskeleton(gameGrid, heroY, heroX, name,
					healthPower, minDamage, maxDamage,
					armor, dodge, armorBonus);
      monsters.push_back(ex);
      break;
    }
    case 2: {
      double dodgeBonus = 0.1 + 0.05*averageLevel;
      Spirit* spirit = new Spirit(gameGrid, heroY, heroX, name,
				  healthPower, minDamage, maxDamage,
				  armor, dodge, dodgeBonus);
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
      heroes[i]->setHealthPower(health + health*0.01);
      if (heroes[i]->getHealthPower() > heroes[i]->getMaxHealthPower()) {
	heroes[i]->setHealthPower(heroes[i]->getMaxHealthPower());
      }
      if (mana == 0) {
	heroes[i]->setMagicPower(100);
      } else {
	heroes[i]->setMagicPower(mana + mana*0.1);
	if (heroes[i]->getMagicPower() > heroes[i]->getMaxMagicPower()) {
	  heroes[i]->setMagicPower(heroes[i]->getMaxMagicPower());
	}
      }
    }
  }
  list<Monster*> :: const_iterator it = monsters.begin();
  for ( ; it != monsters.end(); ++it) {
    int health = (*it)->getHealthPower();
    (*it)->setHealthPower(health + health*0.01);
    if ((*it)->getHealthPower() > (*it)->getMaxHealthPower()) {
      (*it)->setHealthPower((*it)->getMaxHealthPower());
    }
  }
}

void updatePotionsAndNerfs(void) {
  for (size_t i = 0U; i != heroes.size(); ++i) {
    heroes[i]->updatePotions();   
  }
  list<Monster*> :: iterator it = monsters.begin();
  for ( ; it != monsters.end(); ++it) {
    (*it)->updateNerfs();
  }
}

void createHeroes(int numberOfHeroes) {
  bool warriorSelected = false;
  bool sorcererSelected = false;
  bool paladinSelected = false;
  for (int i = 0; i != numberOfHeroes; ++i) {
    cout << "Please enter a class for hero " << i + 1
	 << " ( possible classes are ";
    if (!warriorSelected) cout << "Warrior ";
    if (!sorcererSelected) cout << "Sorcerer ";
    if (!paladinSelected) cout << "Paladin ";
    cout << ")" << endl << endl << "> ";
    string heroClass;
    cin >> heroClass;
    transform(heroClass.begin(), heroClass.end(),
	      heroClass.begin(), :: tolower);
    if (!(heroClass == "warrior"
	  || heroClass == "paladin"
	  || heroClass == "sorcerer")
	) {
      cout << "That's not a valid class!" << endl;
      --i;
      continue;
    }

    if (heroClass == "warrior" && warriorSelected) {
      cout << endl
	   << "Warrior is already selected. Please select one of the "
	   << "available classes" << endl << endl;
      --i;
      continue;
    }
    if (heroClass == "sorcerer" && sorcererSelected) {
      cout << endl
	   << "Sorcerer is already selected. Please selecet one of the "
	   << "available classes" << endl << endl;
      --i;
      continue;
    }
    if (heroClass == "paladin" && paladinSelected) {
      cout << endl
	   << "Paladin is already selected. Please select one of the "
	   << "available classes" << endl << endl;
      --i;
      continue;
    }

    cout << endl << "Please enter a name for your hero"
	 << endl << endl << "> ";
    string name;
    cin >> name;
    cout << endl;
    Hero* hero;
    if (heroClass == "warrior") {
      warriorSelected = true;
      hero = new Warrior(gameGrid, name);
    } else if (heroClass == "sorcerer") {
      sorcererSelected = true;
      hero = new Sorcerer(gameGrid, name);
    } else if (heroClass == "paladin") {
      paladinSelected = true;
      hero = new Paladin(gameGrid, name);
    }

    heroes.push_back(hero);
  }
}

void readData(void) {
  ifstream inputStream;
  vector<string>* dataVectors[5] = {
    &names, &weapons, &armors,
    &potions, &spells
  };
  string inputNames[5] = {
    "input/names.txt",
    "input/weapons.txt",
    "input/armors.txt",
    "input/potions.txt",
    "input/spells.txt"
  };
  for (size_t i = 0U; i != 5U; ++i) {
    inputStream.open(inputNames[i].c_str());
    if (inputStream.is_open() == false) {
      cerr << "There was an error while opening "
	   << inputNames[i] << " file. Exiting game..."
	   << endl;
      exit(EXIT_FAILURE);
      
    }
    readSpecificData(inputStream, *dataVectors[i]);
    inputStream.close();
  }
}

void readSpecificData(ifstream& stream, vector<string>& data) {
  while (stream.eof() == false) {
    getline(stream, buffer);
    data.push_back(buffer);
  }
}

void setMap(void) {
  map.open("input/map.txt");
  if (!map.is_open()) {
    cerr << "There was a problem opening the map file.\nExiting game..."
	 << endl;
    exit(EXIT_FAILURE);
  }
}

int getNumberOfHeroes(void) {
  int numberOfHeroes = -1;
  while (numberOfHeroes < 1 || numberOfHeroes > 3) {
    cout << endl
	 << "Please enter the number of heroes you want to have "
	 << "(min: 1, max: 3)" << endl << endl << "> ";
    cin >> numberOfHeroes;    
    cout << endl;
    cin.ignore(numeric_limits<streamsize> :: max(), '\n');
  }
  return numberOfHeroes;
}

void cleanupResources(void) {  
  delete gameGrid;
  heroes.clear();
  names.clear();
  weapons.clear();
  armors.clear();
  potions.clear();
  spells.clear();
  map.close();
  quitGame = false;
}

void play(void) {
  setMap();
  readData();
  int numberOfHeroes = getNumberOfHeroes();
  initGrid();
  createHeroes(numberOfHeroes);
  int heroTurn = 0;
  bool battled = false;
  while (quitGame == false) {
    Hero* currentHero = heroes[heroTurn];
    heroTurn = (heroTurn + 1) % numberOfHeroes;
    cout << endl << "Hero Playing: "
	 << currentHero->getName() << endl;
    if (!battled && currentHero->getTile().isQualifiedForBattle(numberOfHeroes)) {
      if (rng.boolean(battleProbability)) {
    	handleBattleCase();
	currentHero->updatePotions();
	battled = true;
	continue;
      }      
    }
    handleBasicCase(currentHero);
    battled = false;
  }
  cleanupResources();
}

void run(void) {  
  MainMenu mainMenu;
  string userInput;
  bool firstWelcome = true;

  do {
	if (firstWelcome) {
		mainMenu.welcome();
		firstWelcome = false;
	} else {
		mainMenu.displayMenu();
	}

    userInput = mainMenu.prompt();
    transform(userInput.begin(), userInput.end(),	      
	      userInput.begin(), :: tolower);

    if (userInput == "generatemap") {
      generateMap();
    } else if (userInput == "play") {
      play();
    } else if (userInput == "help") {
       mainMenu.help();
    } 
    clearScreen();	// When exiting from any case. Print ClearScreen.
  } while (userInput != "quit");
  cout << endl << "Exiting game..." << endl;
}

//

void clearScreen(void) {
  // Yes I know, that way is pathetic... :)
  cout << string(100, '\n');
}

int getDigits(int n) {
  if (n == 0) return 1;
  int digits = 0;
  while (n) {
    ++digits;
    n /= 10;
  }
  return digits;
}

void printHeroFrame(void) {
  cout << '+' << string(16, '-');
  cout << '+' << string(7, '-');
  cout << '+' << string(8, '-');
  cout << '+' << string(8, '-');
  cout << '+' << string(12, '-');
  cout << '+' << string(11, '-');
  cout << '+' << string(13, '-');
  cout << '+' << string(15, '-');
  cout << '+' << string(16, '-');
  cout << '+' << endl;
}

void printMonsterFrame(void) {
  cout << '+' << string(24, '-'); // NAME
  cout << '+' << string(9, '-');  // LEVEL
  cout << '+' << string(8, '-');  // HP
  cout << '+' << string(12, '-'); // MIN DAMAGE
  cout << '+' << string(12, '-'); // MAX DAMAGE
  cout << '+' << string(9, '-');  // ARMOR
  cout << '+' << string(9, '-');  // DODGE
  cout << '+' << endl;
}
