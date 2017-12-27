/*
 * Weapon.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>

#include "Weapon.h"

using namespace std;

Weapon::Weapon(
	string name,
	int val,
	int s,
	int minL,
	int dmg, bool both
)
: Item(name, val, s, minL), damage(dmg), requiresBothHands(both)
{
	cout << "Weapon constructed..." << endl;
}

Weapon::~Weapon() {
	cout << "Weapon destroyed !!!" << endl;
}

int Weapon::getDamage() const {
	return damage;
}

string Weapon::getInfo() const {
	stringstream result;

	result << Item::getInfo()
		<< "damage: " << damage << endl
		<< "requiresBothHands: " << ( requiresBothHands ? "Yes" : "No" ) << endl;

	return result.str();
}

