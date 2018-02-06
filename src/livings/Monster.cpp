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

