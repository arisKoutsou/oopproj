// Battle.h --- 
// 
// Filename: Battle.h
// Author: George Liontos
// Created: Fri Jan 12 17:32:28 2018 (+0200)

#if !defined(__BATTLE_HEADER__)
#define __BATTLE_HEADER__

#include <list>
#include <string>

using namespace std;

class Living;
class Monster;
class Hero;

class Battle {
public:
  Battle(const list<Living*>& livings);
  ~Battle();

  void beginBattle();
  void setHeroesWon(bool result);
private:
  Living* getLivingByName(const string& name);
  void printMonsters() const;
  Living* currentAttacker;
  Living* currentDefender;
  list<Monster*> monsters;
  list<Hero*> heroes;
  bool heroesWon;
  bool heroesRound;
};

#endif
