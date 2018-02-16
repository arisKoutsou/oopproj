/*
 * Armor.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>
#include <iomanip>

#include "../../include/game_utils.h"
#include "../../include/Armor.h"

using namespace std;

Armor::Armor(
	string name,
	int val,
	int s,
	int minL,
	double reduce
)
: Item(name, val, s, minL), reduceDamageTakenBy(reduce) {}

Armor::~Armor() {}

double Armor::getDamageReductionFactor() const {
	return reduceDamageTakenBy;
}

void Armor::getInfo() const {
  size_t nameLength = getName().length();
  int priceDigits = getDigits(buyFor());
  int minLevelDigits = getDigits(unlocksInLevel());
  int factorDigits = getDigits(getDamageReductionFactor()) + 2;
  printArmorFrame();
  cout << '|'
       << setw(12 + nameLength/2) << getName() << setw(13 - nameLength/2) << '|'
       << setw(3 + priceDigits/2) << buyFor() << setw(5 - priceDigits/2) << '|'
       << setw(6 + minLevelDigits/2) << unlocksInLevel() << setw(6 - minLevelDigits/2) << '|'
       << setw(9 + factorDigits/2) << setprecision(2) << getDamageReductionFactor()
       << setw(10 - factorDigits/2) << '|'
       << endl;
}

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
