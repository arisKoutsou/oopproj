/*
 * Monster.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "./Monster.h"

Monster::Monster(
	Grid* gr,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg,
	int x,
	int y
)
: Living(gr, nam, hp, x, y),
  minDamage(min),
  maxDamage(max),
  armor(arm), dodge(dodg)
{

}

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
