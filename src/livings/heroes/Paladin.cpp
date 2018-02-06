/*
 * Paladin.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Paladin.h"
#include "../Hero.h"

Paladin::Paladin(
	Grid* gr,
	string nam,
	int y,
	int x,
	int hp,
	int mp,
	int s,
	double a,
	int d
) : strengthBonus(0.1), dexterityBonus(0.1),
    Hero(gr, nam, y, x, hp, mp, s, a, d) {

  this->strength = s + (s * strengthBonus);
  this->dexterity = d + (d * dexterityBonus);
}

void Paladin::levelUp() {
	Hero::levelUp();
	dexterity += dexterity*dexterityBonus;
	strength += strength*strengthBonus;
}

// Implemented by: (George Liontos)
bool Paladin :: operator==(const Paladin& rValue) const {
  bool sameHeros;
  bool sameStrengthBonus;
  bool sameDexterityBonus;

  sameHeros = Hero::operator==(rValue);
  sameStrengthBonus = (this->strengthBonus == rValue.strengthBonus)
    ? true : false;
  sameDexterityBonus = (this->dexterityBonus == rValue.dexterityBonus)
    ? true : false;

  return (sameHeros && sameStrengthBonus && sameDexterityBonus);
}
