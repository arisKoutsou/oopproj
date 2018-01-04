/*
 * Sorcerer.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Sorcerer.h"

Sorcerer::Sorcerer(
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : Hero(nam, hp, mp, s, a*agilityBonus, d*dexterityBonus) {

}

void Sorcerer::levelUp() {
	dexterity += dexterity*dexterityBonus;
	agility += agility*agilityBonus;
}


