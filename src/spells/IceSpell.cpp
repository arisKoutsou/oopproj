/*
 * IceSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include "IceSpell.h"
#include "iomanip"

IceSpell::IceSpell(
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
  oponentDamageReduction(reduction),
  rounds(rnds)
{
	// Put cnstr.
}

double IceSpell::reduceOponentDamageRangeBy() const {
	return oponentDamageReduction;
}

int IceSpell::getReductionRounds() const {
	return rounds;
}

string IceSpell::getInfo() const {
	stringstream result;
	result << fixed << setprecision(2);

	result << Spell::getInfo()
		<< "oponent damage reduction: "
		<< oponentDamageReduction*100 << "%" << endl
		<< "takes effect for: "
		<< rounds << " rounds" << endl;

	return result.str();
}
