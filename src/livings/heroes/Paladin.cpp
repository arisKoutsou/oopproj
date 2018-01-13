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
	int y,
	int x,
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : strengthBonus(0.1), dexterityBonus(0.1),
    Hero(gr, y, x, nam, hp, mp, s, a, d) {

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
