/*
 * Living.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */
#include <iostream>

#include "../../include/Living.h"

Living::Living(
	string nam,
	int hp
)
: name(nam), healthPower(hp), level(1)	// Level start at 1.
{
	cout << "Living constructed..." << endl;
}

Living::~Living() {
	cout << "Living destroyed !!!" << endl;
}

int Living::getHealthPower() const {
	return healthPower;
}

int Living::getLevel() const {
	return level;
}

const string& Living::getName() const {
	return name;
}
