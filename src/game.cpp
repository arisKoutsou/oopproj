#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "game_utils.h"
#include "livings/Hero.h"
#include "random/Random.h"

using namespace std;

vector<Hero*> heroes;
list<Monster*> monsters;
Grid* gameGrid;
bool quitGame = false;
int rows = 10;
int columns = 15;
const Random rng;
static const double battleProbability = 0.6;

int main(int argc, char* argv[]) {  
  int numberOfHeroes;
  while (numberOfHeroes < 1 || numberOfHeroes > 3) {
    cout << "Please enter the number of heroes you want to have "
	 << "(min: 1, max: 3): ";
    cin >> numberOfHeroes;
  }
  ifstream map(argv[1]);
  initGrid(map);
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
  map.close();
  delete gameGrid;
  return EXIT_SUCCESS;
}
