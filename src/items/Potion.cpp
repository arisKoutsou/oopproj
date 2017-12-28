/*
 * Potion.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Potion.h"

using namespace std;

Potion::Potion(
	string name,
	int val,
	int s,
	int minL,
	double sB,
	double dB,
	double aB
)
: Item(name, val, s, minL),
  agilityBoost(aB),
  strengthBoost(sB),
  dexterityBoost(dB)
{
	cout << "Potion constructed..." << endl;
}

Potion::~Potion() {
	cout << "Potion destroyed !!!" << endl;
}

double Potion::getAgilityBoost() const {
	return agilityBoost;
}

double Potion::getDexterityBoost() const {
	return dexterityBoost;
}

double Potion::getStrengthBoost() const {
	return strengthBoost;
}

string Potion::getInfo() const {
	stringstream result;
	result << fixed << setprecision(2);

	result << Item::getInfo();

	if (agilityBoost != 0.0) {
		result << "agilityBoost: "
			<< agilityBoost*100 << "%" << endl;
	}
	if (strengthBoost != 0.0) {
		result << "strengthBoost: "
			<< strengthBoost*100 << "%" << endl;
	}
	if (dexterityBoost != 0.0) {
		result << "dexterityBoost: "
			<< dexterityBoost*100 << "%" << endl;
	}

	return result.str();
}

// Implemented by: (George Liontos)
bool Potion :: operator==(const Potion& rValue) const {
  bool sameItems;
  bool sameStrengthBoost;
  bool sameDexterityBoost;
  bool sameAgilityBoost;

  sameItems = (static_cast<Item>(*this) == rValue);

  sameStrengthBoost = (this->strengthBoost == rValue.strengthBoost)
                       ? true : false;

  sameDexterityBoost = (this->dexterityBoost == rValue.dexterityBoost)
                        ? true : false;

  sameAgilityBoost = (this->agilityBoost == rValue.agilityBoost)
                      ? true : false;

  return (sameStrengthBoost &&
	  sameDexterityBoost &&
	  sameAgilityBoost &&
	  sameItems);
}
