/*
 * Monster.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */
#include <iostream>

#include "./Monster.h"

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
  armor(arm), dodge(dodg) {}

int Monster::getArmor() const {
	return armor;
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

void Monster::dealDamage(int damageDealt) {
	Living::dealDamage(damageDealt);
	if (this->getHealthPower() <= 0) {
		cout << "A monster died..." << endl; // This needs fixing...
	}
}


