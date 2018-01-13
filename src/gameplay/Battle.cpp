// Battle.cpp --- 
// 
// Filename: Battle.cpp
// Author: George Liontos
// Created: Fri Jan 12 17:32:07 2018 (+0200)

#include <iostream>
#include <list>
#include "Battle.h"
#include "../random/Random.h"
#include "../livings/Living.h"

Battle :: Battle(int _rounds, const list<Living*>& livings)

  : rounds(_rounds), heroesWon(false), heroesRound(true) {

  list<Living*> :: const_iterator it = livings.begin();
  for ( ; it != livings.end(); ++it) {
    if ((*it)->kindOf() == "Hero") {
      heroes.push_front(*it);
    } else {
      monsters.push_front(*it);
    }
  }

  currentAttacker = heroes.front();
  currentDefender = monsters.front();
}

Battle :: ~Battle() {}

void Battle :: setHeroesWon(bool result) {
  heroesWon = result;
}

void Battle :: nextRound() {
  if (this->rounds <= 0) return;
  --this->rounds;
  // TODO (George): Every time the round changes search for the valid
  // hero (Health > 0) and set him as the attacker
}

bool Battle :: battleEnded() const {
  return (this->rounds == 0);
}
