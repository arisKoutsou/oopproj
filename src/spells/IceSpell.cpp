/*
 * IceSpell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#include <iomanip>
#include <sstream>
#include "./IceSpell.h"

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
  rounds(rnds) {}

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

// Imlemented by: (George Liontos)
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
