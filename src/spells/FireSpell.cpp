/*
 * FireSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include "FireSpell.h"
#include "iomanip"

FireSpell::FireSpell(
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
  oponentArmorReduction(reduction),
  rounds(rnds)
{
	// Put cnstr.
}

double FireSpell::reduceOponentArmorBy() const {
	return oponentArmorReduction;
}

int FireSpell::getReductionRounds() const {
	return rounds;
}

string FireSpell::getInfo() const {
	stringstream result;
	result << fixed << setprecision(2);

	result << Spell::getInfo()
		<< "oponent armor reduction: "
		<< oponentArmorReduction*100 << "%" << endl
		<< "takes effect for: "
		<< rounds << " rounds" << endl;

	return result.str();
}
