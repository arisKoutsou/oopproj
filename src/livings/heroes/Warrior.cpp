/*
 * Warrior.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Warrior.h"

Warrior::Warrior(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
) : agilityBonus(0.1), strengthBonus(0.1),
  Hero(gr, y, x, nam, hp, mp, strength, a, d) {

  this->strength = s + (s * strengthBonus);
  this->agility = a + (a * agilityBonus);
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

  sameHeros = Hero::operator==(rValue);
  sameAgilityBonus = (this->agilityBonus == rValue.agilityBonus)
    ? true : false;
  sameStrengthBonus = (this->strengthBonus == rValue.strengthBonus)
    ? true : false;

  return (sameHeros && sameAgilityBonus && sameStrengthBonus);
}
