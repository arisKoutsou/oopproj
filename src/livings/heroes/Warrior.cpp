/*
 * Warrior.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Warrior.h"

Warrior::Warrior(
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : Hero(nam, hp, mp, s*strengthBonus, a*agilityBonus, d),
    agilityBonus(0.1), strengthBonus(0.1) {

}

void Warrior::levelUp() {
	strength += strength*strengthBonus;
	agility += agility*agilityBonus;
}

// Implemented by: (George Liontos)
bool Warrior :: operator==(const Warrior& rValue) const {
  bool sameHeros;
  bool sameAgilityBonus;
  bool sameStrengthBonus;

  sameHeros = (static_cast<Hero>(*this) == rValue);
  sameAgilityBonus = (this->agilityBonus == rValue.agilityBonus)
    ? true : false;
  sameStrengthBonus = (this->strengthBonus == rValue.strengthBonus)
    ? true : false;

  return (sameHeros && sameAgilityBonus && sameStrengthBonus);
}
