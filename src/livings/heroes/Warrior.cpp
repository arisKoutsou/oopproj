/*
 * Warrior.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Warrior.h"

Warrior::Warrior(
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : Hero(nam, hp, mp, s*strengthBonus, a*agilityBonus, d) {

}

void Warrior::levelUp() {
	strength += strength*strengthBonus;
	agility += agility*agilityBonus;
}
