/*
 * Monster.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */
#include <iostream>
#include <iomanip>

#include "../../include/game_utils.h"
#include "../../include/Monster.h"
#include "../../include/Hero.h"
#include "../../include/Random.h"

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
	double arm,
	double dodg        
)
: Living(gr, y ,x, nam, hp),
  minDamage(min),
  maxDamage(max),
  damageReductionFactor(arm), dodge(dodg) {}

double Monster::getDamageReductionFactor() const {
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

void Monster :: setLevel(int level) {
  this->level = level;
}

void Monster::printStats() const {
  size_t nameLength = getName().length();
  int levelDigits = getDigits(level);
  int hpDigits = getDigits(getHealthPower());
  int minDamageDigits = getDigits(minDamage);
  int maxDamageDigits = getDigits(maxDamage);
  int armorDigits = getDigits(getDamageReductionFactor()) + 2;
  int dodgeDigits = getDigits(getDodge()) + 2;
  printMonsterFrame();
  cout << '|'
       << setw(13 + nameLength/2) << getName() << setw(12 - nameLength/2) << '|'
       << setw(5 + levelDigits/2) << level << setw(5 - levelDigits/2) << '|'
       << setw(5 + hpDigits/2) << getHealthPower() << setw(4 - hpDigits/2) << '|'
       << setw(6 + minDamageDigits/2) << minDamage << setw(7 - minDamageDigits/2) << '|'
       << setw(6 + maxDamageDigits/2) << maxDamage << setw(7 - maxDamageDigits/2) << '|'
       << setw(5 + armorDigits/2) << setprecision(2) << getDamageReductionFactor()
       << setw(5 - armorDigits/2) << '|'
       << setw(5 + dodgeDigits/2) << setprecision(2) << getDodge() << setw(5 - dodgeDigits/2) << '|'
       << endl;
}

void Monster::receiveDamage(int damageDealt) {
  Living::receiveDamage(damageDealt);
  if (this->getHealthPower() == 0) {
    cout << "A monster died..." << endl;
  }
}

void Monster::attack(Hero* hero) {
  Random random;

  if (random.boolean(hero->getAgility())) {
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
