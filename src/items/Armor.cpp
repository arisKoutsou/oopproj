/*
 * Armor.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>
#include <iomanip>

#include "./Armor.h"

using namespace std;

Armor::Armor(
	string name,
	int val,
	int s,
	int minL,
	double reduce
)
: Item(name, val, s, minL), reduceDamageTakenBy(reduce)
{
	cout << "Armor constructed..." << endl;
}

Armor::~Armor() {
	cout << "Armor destroyed !!!" << endl;
}

double Armor::getDamageReductionFactor() const {
	return reduceDamageTakenBy;
}

string Armor::getInfo() const {
	stringstream result;
	result << fixed << setprecision(2);

	result << Item::getInfo()
	       << "reduces damage taken by: "
	       << reduceDamageTakenBy*100 << "%" << endl;

	return result.str();
}

// Implemented by: (George Liontos)
bool Armor :: operator==(const Armor& rValue) const {
  bool sameItems;
  bool sameReduceDamageTakenBy;

  sameItems = Item::operator==(rValue);
  sameReduceDamageTakenBy =
    (this->reduceDamageTakenBy == rValue.reduceDamageTakenBy)
    ? true : false;

  return (sameItems && sameReduceDamageTakenBy);
}

string Armor :: kindOf() const {
  return "Armor";
}
