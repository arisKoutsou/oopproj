/*
 * Weapon.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Weapon.h"
#include "../game_utils.h"
#include "../items/Item.h"

using namespace std;

Weapon::Weapon(
	string name,
	int val,
	int s,
	int minL,
	int dmg, bool both
)
: Item(name, val, s, minL), damage(dmg), requiresBothHands(both) {}

Weapon::~Weapon() {}

int Weapon::getDamage() const {
	return damage;
}

void Weapon :: getInfo() const {
  size_t nameLength = getName().length();
  int priceDigits = getDigits(buyFor());
  int minLevelDigits = getDigits(unlocksInLevel());
  int damageDigits = getDigits(damage);
  string twoHanded = (requiresBothHands) ? "YES" : "NO";
  printWeaponFrame();
  cout << '|'
       << setw(12 + nameLength/2) << getName() << setw(13 - nameLength/2) << '|'
       << setw(3 + priceDigits/2) << buyFor() << setw(5 - priceDigits/2)<< '|'
       << setw(6 + minLevelDigits/2) << unlocksInLevel() << setw(6 - minLevelDigits/2) << '|'
       << setw(4 + damageDigits/2) << damage << setw(5 - damageDigits/2) << '|'
       << setw(6 + twoHanded.length()/2) << twoHanded << setw(7 - twoHanded.length()/2) << '|'
       << endl;
}

bool Weapon :: operator==(const Weapon& rValue) const {
  bool sameItems;
  bool sameDamage;
  bool sameRequiresBothHands;

  sameItems = Item::operator==(rValue);
  sameDamage = (this->damage == rValue.damage) ? true : false;
  sameRequiresBothHands = (this->requiresBothHands == rValue.requiresBothHands)
                           ? true : false;

  return (sameItems && sameDamage && sameRequiresBothHands);
}

string Weapon :: kindOf() const {
  return "Weapon";
}

bool Weapon :: needsBothHands() const {
  return requiresBothHands;
}
