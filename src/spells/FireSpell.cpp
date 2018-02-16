/*
 * FireSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../../include/game_utils.h"
#include "../../include/FireSpell.h"

using namespace std;

FireSpell::FireSpell(
	string 	nam,
	int 	val,
	int 	minL,
	int 	magicP,
	int	minDmg,
	int 	maxDmg,
	double  reduction,
	int rnds
)
: Spell(nam, val, minL, magicP, minDmg, maxDmg),
  oponentArmorReduction(reduction),
  rounds(rnds) {}

double FireSpell::reduceOponentArmorBy() const {
	return oponentArmorReduction;
}

int FireSpell::getReductionRounds() const {
	return rounds;
}

void FireSpell::getInfo() const {
  size_t nameLength = getName().length();
  int priceDigits = getDigits(getValue());
  int levelDigits = getDigits(getMinLevel());
  int manaDigits = getDigits(getMagicPowerRequired());
  int minDamageDigits = getDigits(getMinDamage());
  int maxDamageDigits = getDigits(getMaxDamage());
  int nerfDigits = getDigits(reduceOponentArmorBy()) + 2;
  int durationDigits = getDigits(getReductionRounds());  
  printFireSpellFrame();
  cout << '|'
       << setw(12 + nameLength/2) << getName() << setw(13 - nameLength/2) << '|'
       << setw(3 + priceDigits/2) << getValue() << setw(5 - priceDigits/2) << '|'
       << setw(6 + levelDigits/2) << getMinLevel() << setw(6 - levelDigits/2) << '|'
       << setw(5 + manaDigits/2) << getMagicPowerRequired() << setw(7 - manaDigits/2) << '|'
       << setw(6 + minDamageDigits/2) << getMinDamage() << setw(7 - minDamageDigits/2) << '|'
       << setw(6 + maxDamageDigits/2) << getMaxDamage() << setw(7 - maxDamageDigits/2) << '|'
       << setw(9 + nerfDigits/2) << setprecision(2) << reduceOponentArmorBy()
       << setw(9 - nerfDigits/2) << '|'
       << setw(5 + durationDigits/2) << getReductionRounds() << setw(6 - durationDigits/2) << '|'
       << endl;  
}

bool FireSpell :: operator==(const FireSpell& rValue) const {
  bool sameSpells;
  bool sameOponentArmorReduction;
  bool sameRounds;

  sameSpells = Spell::operator==(rValue);
  sameOponentArmorReduction =
    (this->oponentArmorReduction == rValue.oponentArmorReduction) ? true : false;
  sameRounds = (this->rounds == rValue.rounds) ? true : false;

  return (sameSpells && sameOponentArmorReduction && sameRounds);
}

const string FireSpell :: kindOf() const {
  return "FireSpell";
}
