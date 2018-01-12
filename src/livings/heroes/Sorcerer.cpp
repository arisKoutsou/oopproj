/*
 * Sorcerer.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */
#include "Sorcerer.h"

Sorcerer::Sorcerer(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : agilityBonus(0.1), dexterityBonus(0.1),
    Hero(gr, y, x, nam, hp, mp, s, a, d) {

  this->agility = a + (a * agilityBonus);
  this->dexterity = d + (d * dexterityBonus);
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

  sameHeros = Hero::operator==(rValue);
  sameAgilityBonus = (this->agilityBonus == rValue.agilityBonus)
    ? true : false;
  sameDexterityBonus = (this->dexterityBonus == rValue.dexterityBonus)
    ? true : false;

  return (sameHeros && sameAgilityBonus && sameDexterityBonus);
}
