/*
 * Monster.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

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
: Living(gr, nam, hp, y, x),
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
