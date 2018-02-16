/*
 * Potion.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>
#include <iomanip>

#include "../../include/game_utils.h"
#include "../../include/Potion.h"

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
  size_t nameLength = getName().length();
  int priceDigits = getDigits(buyFor());
  int minLevelDigits = getDigits(unlocksInLevel());
  int strengthDigits = getDigits(getStrengthBoost()) + 2;
  int agilityDigits = getDigits(getAgilityBoost()) + 2;
  int dexDigits = getDigits(getDexterityBoost()) + 2;
  int durDigits = getDigits(getRoundsEffective());
  printPotionFrame();
  cout << '|'
       << setw(12 + nameLength/2) << getName() << setw(13 - nameLength/2) << '|'
       << setw(3 + priceDigits/2) << buyFor() << setw(5 - priceDigits/2) << '|'
       << setw(6 + minLevelDigits/2) << unlocksInLevel() << setw(6 - minLevelDigits/2) << '|'
       << setw(8 + strengthDigits/2) << setprecision(2) << getStrengthBoost()
       << setw(9 - strengthDigits/2) << '|'
       << setw(8 + dexDigits/2) << setprecision(2) << getDexterityBoost()
       << setw(10 - dexDigits/2) << '|'
       << setw(9 + agilityDigits/2) << setprecision(2) << getAgilityBoost()
       << setw(7 - agilityDigits/2) << '|'
       << setw(5 + durDigits/2) << getRoundsEffective() << setw(6 - durDigits/2) << '|'
       << endl;
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
