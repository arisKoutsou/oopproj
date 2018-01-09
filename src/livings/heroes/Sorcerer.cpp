/*
 * Sorcerer.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */
#include "Sorcerer.h"

Sorcerer::Sorcerer(
	Grid* gr,
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d,
	int x,
	int y
) : Hero(gr, nam, hp, mp, s, a*agilityBonus, d*dexterityBonus, x, y),
    agilityBonus(0.1), dexterityBonus(0.1) {

}

void Sorcerer::levelUp() {
	dexterity += dexterity*dexterityBonus;
	agility += agility*agilityBonus;
}

// Implemented by: (George Liontos)
bool Sorcerer :: operator==(const Sorcerer& rValue) const {
  bool sameHeros;
  bool sameAgilityBonus;
  bool sameDexterityBonus;

  sameHeros = (static_cast<Hero>(*this) == rValue);
  sameAgilityBonus = (this->agilityBonus == rValue.agilityBonus)
    ? true : false;
  sameDexterityBonus = (this->dexterityBonus == rValue.dexterityBonus)
    ? true : false;

  return (sameHeros && sameAgilityBonus && sameDexterityBonus);
}
