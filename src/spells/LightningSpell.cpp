/*
 * LightningSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../../include/game_utils.h"
#include "../../include/LightningSpell.h"

using namespace std;

LightningSpell::LightningSpell(
	string 	nam,
	int 	val,
	int 	minL,
	int 	magicP,
	int		minDmg,
	int 	maxDmg,
	double  reduction,	// new data member.
	int rnds
)
: Spell(nam, val, minL, magicP, minDmg, maxDmg),
  oponentDodgeReduction(reduction),
  rounds(rnds) {}

double LightningSpell::reduceOponentDodgeBy() const {
	return oponentDodgeReduction;
}

int LightningSpell::getReductionRounds() const {
	return rounds;
}

void LightningSpell::getInfo() const {
  size_t nameLength = getName().length();
  int priceDigits = getDigits(getValue());
  int levelDigits = getDigits(getMinLevel());
  int manaDigits = getDigits(getMagicPowerRequired());
  int minDamageDigits = getDigits(getMinDamage());
  int maxDamageDigits = getDigits(getMaxDamage());
  int nerfDigits = getDigits(reduceOponentDodgeBy()) + 2;
  int durationDigits = getDigits(getReductionRounds());  
  printLightningSpellFrame();
  cout << '|'
       << setw(12 + nameLength/2) << getName() << setw(13 - nameLength/2) << '|'
       << setw(3 + priceDigits/2) << getValue() << setw(5 - priceDigits/2) << '|'
       << setw(6 + levelDigits/2) << getMinLevel() << setw(6 - levelDigits/2) << '|'
       << setw(5 + manaDigits/2) << getMagicPowerRequired() << setw(7 - manaDigits/2) << '|'
       << setw(6 + minDamageDigits/2) << getMinDamage() << setw(7 - minDamageDigits/2) << '|'
       << setw(6 + maxDamageDigits/2) << getMaxDamage() << setw(7 - maxDamageDigits/2) << '|'
       << setw(9 + nerfDigits/2) << setprecision(2) << reduceOponentDodgeBy()
       << setw(9 - nerfDigits/2) << '|'
       << setw(5 + durationDigits/2) << getReductionRounds() << setw(6 - durationDigits/2) << '|'
       << endl;    
}

bool LightningSpell :: operator==(const LightningSpell& rValue) const {
  bool sameSpells;
  bool sameOponentDodgeReduction;
  bool sameRounds;

  sameSpells = Spell::operator==(rValue);;
  sameOponentDodgeReduction =
    (this->oponentDodgeReduction == rValue.oponentDodgeReduction) ? true : false;
  sameRounds = (this->rounds == rValue.rounds) ? true : false;

  return (sameSpells && sameOponentDodgeReduction && sameRounds);
}

const string LightningSpell :: kindOf() const {
  return "LightningSpell";
}
