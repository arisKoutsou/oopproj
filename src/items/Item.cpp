/*
 * Item.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>

#include "./Item.h"

using namespace std;

Item::Item(
	string nam,
	int val,
	int s,
	int minL
)
: name(nam), value(val),
  sellFor(s), minLevel(minL),
  sellRate(0.5) {}

Item::~Item() {}

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
		<< "price: " << buyFor() << endl
		<< "sell for: " << sellsFor() << endl
		<< "min level to aquire: " << minLevel << endl;

	return result.str();
}

// Implemented by: (George Liontos)
bool Item :: operator==(const Item& rValue) const {
  bool sameName;
  bool sameValue;
  bool sameSellingPrice;
  bool sameMinLevel;

  sameName = (this->name == rValue.name) ? true : false;
  sameValue = (this->value == rValue.value) ? true : false;
  sameSellingPrice = (this->sellFor == rValue.sellFor) ? true : false;
  sameMinLevel = (this->minLevel == rValue.minLevel) ? true : false;

  return (sameName && sameValue && sameSellingPrice && sameMinLevel);
}
