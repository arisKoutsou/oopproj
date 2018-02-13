/*
 * Potion.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>
#include <iomanip>

#include "./Potion.h"

using namespace std;

Potion::Potion(
	string name,
	int val,
	int s,
	int minL,
	double sB,
	double dB,
	double aB,
	int r
)
: Item(name, val, s, minL),
  agilityBoost(aB),
  strengthBoost(sB),
  dexterityBoost(dB),
  roundsEffective(r)
{}

Potion::~Potion() {}

double Potion::getAgilityBoost() const {
	return agilityBoost;
}

double Potion::getDexterityBoost() const {
	return dexterityBoost;
}

double Potion::getStrengthBoost() const {
	return strengthBoost;
}

int Potion::getRoundsEffective() const {
	return roundsEffective;
}

void Potion::roundPassed() {
	roundsEffective--;
}

void Potion :: getInfo() const {
  
}

bool Potion :: operator==(const Potion& rValue) const {
  bool sameItems;
  bool sameStrengthBoost;
  bool sameDexterityBoost;
  bool sameAgilityBoost;

  sameItems = Item::operator==(rValue);

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

string Potion :: kindOf() const {
  return "Potion";
}
