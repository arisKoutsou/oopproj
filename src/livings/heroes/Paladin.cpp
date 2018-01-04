/*
 * Paladin.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Paladin.h"

Paladin::Paladin(
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : Hero(nam, hp, mp, s*strengthBonus, a, d*dexterityBonus) {

}

void Paladin::levelUp() {
	dexterity += dexterity*dexterityBonus;
	strength += strength*strengthBonus;
}

