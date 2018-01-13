// Battle.h --- 
// 
// Filename: Battle.h
// Author: George Liontos
// Created: Fri Jan 12 17:32:28 2018 (+0200)

#if !defined(__BATTLE_HEADER__)
#define __BATTLE_HEADER__

#include <list>

using namespace std;

class Living;

class Battle {
public:
  Battle(int rounds, const list<Living*>& livings);
  ~Battle();

  void setHeroesWon(bool result);
  void nextRound();
  bool battleEnded() const;
private:
  Living* currentAttacker;
  Living* currentDefender;
  list<Living*> monsters;
  list<Living*> heroes;
  int rounds;
  bool heroesWon;
  bool heroesRound;
};

#endif
