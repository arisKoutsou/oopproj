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
#include "../livings/Hero.h"
#include "../livings/Monster.h"
#include "../menu/Menu.h"

Battle :: Battle(const list<Living*>& livings)

  : heroesWon(false), heroesRound(true) {

  list<Living*> :: const_iterator it = livings.begin();
  for ( ; it != livings.end(); ++it) {
    if ((*it)->kindOf() == "Hero") {
      heroes.push_front(static_cast<Hero*>(*it));
    } else {
      monsters.push_front(static_cast<Monster*>(*it));
    }
  }

  currentAttacker = heroes.front();
  currentDefender = monsters.front();
}

Battle :: ~Battle() {}

void Battle :: setHeroesWon(bool result) {
  heroesWon = result;
}

void Battle :: beginBattle() {
  while (true) {
    int selection;

    while ((selection = currentAttacker->getBattleMenu().getSelection())) {
      switch (selection) {
      case 1: {
	currentAttacker->printStats();
	break;
      }
      case 2: {
	cout << "The monsters available for attack are:" << endl;
	printMonsters();
	do {
	  cout << "Enter the name of the monster you want to attack" << endl;
	  string name;
	  cin >> name;
	  currentDefender = getLivingByName(name);
	} while (currentDefender == NULL);
	currentAttacker->attack(currentDefender);
	break;
      }
      case 3: {
	cout << "The monsters available for attack are:" << endl;
	printMonsters();
	do {
	  cout << "Enter the name of the monster you want to attack" << endl;
	  string name;
	  cin >> name;
	  currentDefender = getLivingByName(name);
	} while (currentDefender == NULL);
	currentAttacker->castSpell(currentDefender);
	break;
      }
      case 4: {
        
      }
      }
    }
  }
}

Living* Battle :: getLivingByName(const string& name) {
  list<Living*> :: const_iterator it = monsters.begin();
  for ( ; it != monsters.end(); ++it) {
    if ((*it)->getName() == name) {
      return *it;
    }
  }
  return NULL;
}

void Battle :: printMonsters() const {
  list<Living*> :: const_iterator it = monsters.begin();
  for ( ; it != monsters.end(); ++it) {
    (*it)->printStats();
  }
  cout << endl;
}
