/*
 * Monster.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */
#include <iostream>
#include <iomanip>

#include "./Monster.h"
#include "./Hero.h"
#include "../random/Random.h"

Monster :: Nerf :: Nerf(int _duration, double amount, Type _nerfType)
  : duration(_duration), nerfAmount(amount), nerfType(_nerfType) {}

int Monster :: Nerf :: getDuration() const {
  return duration;
}

double Monster :: Nerf :: getNerfAmount() const {
  return nerfAmount;
}

Monster :: Type Monster :: Nerf :: getNerfType() const {
  return nerfType;
}

void Monster :: Nerf :: roundPassed() {
  --duration;
}

Monster::Monster(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg        
)
: Living(gr, y ,x, nam, hp),
  minDamage(min),
  maxDamage(max),
  damageReductionFactor(arm), dodge(dodg) {}

int Monster::getDamageReductionFactor() const {
	return damageReductionFactor;
}

double Monster::getDodge() const {
	return dodge;
}

int Monster::getMaxDamage() const {
	return maxDamage;
}

int Monster::getMinDamage() const {
	return minDamage;
}

string Monster :: kindOf() const {
  return "Monster";
}

void Monster::printStats() const {
  Living::printStats();
  cout << setprecision(2);
  
  cout << "Damage range: " << minDamage << " - " << maxDamage << endl
       << "Dodge: " << dodge*100 << "%" << endl << endl;
}

void Monster::receiveDamage(int damageDealt) {
	Living::receiveDamage(damageDealt);
	if (this->getHealthPower() == 0) {
	  cout << "A monster died..." << endl; // This needs fixing...
	}
}

void Monster::attack(Hero* hero) {
	Random random;

	if ( random.boolean(hero->getAgility()) ) {
		// Dodged the attack.
		// Do nothing.
	} else {
		int monsterDamage = 0;
		// Calculate the damage that the Monster can cause.
		monsterDamage += random.fromMintoMax(this->minDamage, this->maxDamage);

		// Calculate the damage reduction.
		int damageReduction = 0;

		damageReduction += hero->getDamageReductionFactor()*monsterDamage;

		hero->receiveDamage(monsterDamage - damageReduction);
	}

}

void Monster :: applyNerf(int duration, double amount, Type nerfType) {
  Nerf newNerf(duration, amount, nerfType);
  nerfs.push_back(newNerf);
  switch (nerfType) {
  case ICE: {
    minDamage *= 1.0 - amount;
    maxDamage *= 1.0 - amount;
    break;  
  }
  case FIRE: {
    damageReductionFactor -= amount;
    damageReductionFactor = (damageReductionFactor < 0.0) ? 0.0 : damageReductionFactor;
    break;    
  }
  case LIGHT: {
    dodge -= amount;
    dodge = (dodge < 0.0) ? 0.0 : dodge;
    break;
  }
  }
}

void Monster :: updateNerfs() {
  list<Nerf> :: iterator it = nerfs.begin();
  for ( ; it != nerfs.end(); ++it) {
    (*it).roundPassed();
    if ((*it).getDuration() == -1) {
      switch ((*it).getNerfType()) {
      case ICE: {
	minDamage /= 1.0 - (*it).getNerfAmount();
	maxDamage /= 1.0 - (*it).getNerfAmount();
	break;
      }
      case FIRE: {
        damageReductionFactor += (*it).getNerfAmount();
	break;
      }
      case LIGHT: {
	dodge += (*it).getNerfAmount();
	break;
      }
      }
      list<Nerf> :: iterator tmp = it++;
      nerfs.erase(tmp);
    }
  }
}
