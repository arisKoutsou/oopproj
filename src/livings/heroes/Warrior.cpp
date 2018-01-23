/*
 * Warrior.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Warrior.h"

Warrior::Warrior(
	Grid* gr,
	string nam,
	int y,
	int x,
	int hp,
	int mp,
	int s,
	double a,
	int d
) : agilityBonus(0.1), strengthBonus(0.1),
    Hero(gr, nam, y, x, hp, mp, strength, a, d) {

  this->strength = s + (s * strengthBonus);
  this->agility = a + (a * agilityBonus);
}
    

void Warrior::levelUp() {
	Hero::levelUp();
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
