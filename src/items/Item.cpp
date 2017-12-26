/*
 * Item.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: aris
 */

#include "Item.h"
#include <sstream>
#include <iostream>

Item::Item(
	string nam,
	int val,
	int s,
	int minL
)
: name(nam), value(val),
  sellFor(val*sellRate),
  minLevel(minL) {
	// cout << "Item constructed..." << endl;
}

string Item::getName() const {
	return name;
}

int Item::sellsFor() const {
	return sellFor;
}

int Item::buyFor() const {
	return value;
}

int Item::unlocksInLevel() const {
	return minLevel;
}

string Item::getInfo() const {
	stringstream result;
	result << "name: " << name << endl
		   << "price: " << value << endl
		   << "sell for: " << sellFor << endl
		   << "min level to aquire: " << minLevel;
	return result.str();
}
