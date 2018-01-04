/*
 * LightningSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include <iomanip>
#include <sstream>
#include "./LightningSpell.h"

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
  rounds(rnds)
{
	// Put cnstr.
}

double LightningSpell::reduceOponentDodgeBy() const {
	return oponentDodgeReduction;
}

int LightningSpell::getReductionRounds() const {
	return rounds;
}

string LightningSpell::getInfo() const {
	stringstream result;
	result << fixed << setprecision(2);

	result << Spell::getInfo()
		<< "oponent dodge chance reduction: "
		<< oponentDodgeReduction*100 << "%" << endl
		<< "takes effect for: "
		<< rounds << " rounds" << endl;

	return result.str();
}

// Implemented by: (George Liontos)
bool LightningSpell :: operator==(const LightningSpell& rValue) const {
  bool sameSpells;
  bool sameOponentDodgeReduction;
  bool sameRounds;

  sameSpells = (static_cast<Spell>(*this) == rValue);
  sameOponentDodgeReduction =
    (this->oponentDodgeReduction == rValue.oponentDodgeReduction) ? true : false;
  sameRounds = (this->rounds == rValue.rounds) ? true : false;

  return (sameSpells && sameOponentDodgeReduction && sameRounds);
}
