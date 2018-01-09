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
	int hp,
	int mp,
	int s,
	int a,
	int d,
	int x,
	int y
) : Hero(gr, nam, hp, mp, s*strengthBonus, a, d*dexterityBonus, x, y),
    strengthBonus(0.1), dexterityBonus(0.1) {

}

void Paladin::levelUp() {
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
