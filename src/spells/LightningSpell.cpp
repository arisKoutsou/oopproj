/*
 * LightningSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include "LightningSpell.h"
#include "iomanip"

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
