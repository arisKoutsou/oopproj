/*
 * Hero.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#include "../../include/Hero.h"

Hero::Hero(
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
)
: Living(nam, hp),
  magicPower(mp),
  strength(s), agility(a),
  dexterity(d), money(450),
  expirience(0)
{
	// cnstr.
}

int Hero::getAgility() const {
	return agility;
}

int Hero::getDexterity() const {
	return dexterity;
}

int Hero::getExpirience() const {
	return expirience;
}

int Hero::getMagicPower() const {
	return magicPower;
}

int Hero::getMoney() const {
	return money;
}

int Hero::getStrength() const {
	return strength;
}
