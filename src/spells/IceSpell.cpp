/*
 * IceSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../../include/game_utils.h"
#include "../../include/IceSpell.h"

using namespace std;

IceSpell::IceSpell(
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
  oponentDamageReduction(reduction),
  rounds(rnds) {}

double IceSpell::reduceOponentDamageRangeBy() const {
	return oponentDamageReduction;
}

int IceSpell::getReductionRounds() const {
	return rounds;
}

void IceSpell::getInfo() const {
  size_t nameLength = getName().length();
  int priceDigits = getDigits(getValue());
  int levelDigits = getDigits(getMinLevel());
  int manaDigits = getDigits(getMagicPowerRequired());
  int minDamageDigits = getDigits(getMinDamage());
  int maxDamageDigits = getDigits(getMaxDamage());
  int nerfDigits = getDigits(reduceOponentDamageRangeBy()) + 2;
  int durationDigits = getDigits(getReductionRounds());  
  printIceSpellFrame();
  cout << '|'
       << setw(12 + nameLength/2) << getName() << setw(13 - nameLength/2) << '|'
       << setw(3 + priceDigits/2) << getValue() << setw(5 - priceDigits/2) << '|'
       << setw(6 + levelDigits/2) << getMinLevel() << setw(6 - levelDigits/2) << '|'
       << setw(5 + manaDigits/2) << getMagicPowerRequired() << setw(7 - manaDigits/2) << '|'
       << setw(6 + minDamageDigits/2) << getMinDamage() << setw(7 - minDamageDigits/2) << '|'
       << setw(6 + maxDamageDigits/2) << getMaxDamage() << setw(7 - maxDamageDigits/2) << '|'
       << setw(10 + nerfDigits/2) << setprecision(2) << reduceOponentDamageRangeBy()
       << setw(9 - nerfDigits/2) << '|'
       << setw(5 + durationDigits/2) << getReductionRounds() << setw(6 - durationDigits/2) << '|'
       << endl;  
}

bool IceSpell :: operator==(const IceSpell& rValue) const {
  bool sameSpells;
  bool sameOponentDamageReduction;
  bool sameRounds;

  sameSpells = Spell::operator==(rValue);
  sameOponentDamageReduction =
    (this->oponentDamageReduction == rValue.oponentDamageReduction) ? true : false;
  sameRounds = (this->rounds == rValue.rounds) ? true : false;

  return (sameSpells && sameOponentDamageReduction && sameRounds);
}

const string IceSpell :: kindOf() const {
  return "IceSpell";
}
