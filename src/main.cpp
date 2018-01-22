#include <iostream>
#include <cstdlib>
#include <vector>
#include "livings/Hero.h"
#include "grid/Grid.h"
#include "random/Random.h"
#include "livings/heroes/Warrior.h"
#include "livings/heroes/Sorcerer.h"
#include "livings/heroes/Paladin.h"
#include "exceptions/heroExceptions.h"

using namespace std;

static vector<Hero> heroes;
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
	 << "(possible classes are Warrior, Sorcerer, Paladin): ";
    string heroClass;
    cin >> heroClass;
    if (heroClass == "Warrior") {
      Warrior warrior(gameGrid);
      heroes.push_back(warrior);
    } else if (heroClass == "Sorcerer") {
      Sorcerer sorcerer(gameGrid);
      heroes.push_back(sorcerer);
    } else if (heroClass == "Paladin") {
      Paladin paladin(gameGrid);
      heroes.push_back(paladin);
    } else {
      cout << "That's not a valid class!" << endl;
      --i;
    }
  }
}

inline void handleBasicCase(Hero& currentHero) {
  int selection;  
  currentHero.getGameMenu().displayMenu();
  while ((selection = currentHero.getGameMenu().getSelection())) {
    switch (selection) {
    case 1: gameGrid->displayMap(); break;
    case 2: currentHero.printStats(); break;
    case 3: currentHero.checkInventory(); return;
    case 4: {
      bool moved = false;
      while (!moved) {
	cout << "Please enter the direction you want to move"
	     << "possible directions are up, down, left, right: ";
	string answer;
	cin >> answer;
	Hero :: directions direction;
	if (answer == "up") direction = Hero :: UP;
	else if (answer == "down") direction = Hero :: DOWN;
	else if (answer == "left") direction = Hero :: LEFT;
	else if (answer == "right") direction = Hero :: RIGHT;
	try {
	  currentHero.move(direction);
	  moved = true;
	}
	catch (HeroMoveException& e) {
	  cout << e.what() << endl;
	  moved = false;
	}
      }
      return;
    }
    case 5: {
      string answer;
      do {
	cout << "Do you you really want to quit?" << endl;
	cin >> answer;
	if (answer == "yes") {
	  quitGame = true;
	}
      } while (answer != "yes" || answer != "no");
      return;
    }
    default: break;
    }
    currentHero.getGameMenu().clearMenu();
    currentHero.getGameMenu().displayMenu();
  }
}

void handleBattleCase(Hero& currentHero) {
  //  
}

int main(void) {
  initGrid();
  int numberOfHeroes;
  while (ios::badbit == false) {
    cout << "Please enter the number of heroes you want to have: ";
    cin >> numberOfHeroes;
  }
  createHeroes(numberOfHeroes);
  int heroTurn = 0;
  while (quitGame == false) {
    Hero currentHero = heroes[heroTurn];
    if (currentHero.isInBattle() == false) {
      handleBasicCase(currentHero);
    } else {
      handleBattleCase(currentHero);
    }
  }
  return EXIT_SUCCESS;
}
