#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <list>

#include "game_utils.h"
#include "livings/Hero.h"
#include "random/Random.h"

using namespace std;

static const double battleProbability = 0.6;
ifstream map;
bool quitGame = false;

int main(int argc, char* argv[]) {
  checkArgumentsAndSetMap(argc, argv);
  readData(argc, argv);
  int numberOfHeroes = getNumberOfHeroes();
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
  cleanupResources();
  return EXIT_SUCCESS;
}
