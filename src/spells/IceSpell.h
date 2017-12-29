/*
 * IceSpell.h
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#ifndef SPELLS_ICESPELL_H_
#define SPELLS_ICESPELL_H_

#include "Spell.h"

class IceSpell: public Spell {
public:
	IceSpell(
		string 	nam,
		int 	val = 20,
		int 	minL = 1,
		int 	magicP = 10,
		int		minDmg = 80,
		int 	maxDmg = 100,
		double  reduction = 0.2,	// new data member.
		int 	rounds = 2
	);

	// Returns double in [0, 1].
	// The percentage which enemy damage will be reduced.
	double reduceOponentDamageRangeBy() const;
	int    getReductionRounds() const;
	string getInfo() const;

        // Added by: (George Liontos)
        bool operator==(const IceSpell& rValue) const;
private:
	double 	oponentDamageReduction;
	int 	rounds;
};

#endif /* SPELLS_ICESPELL_H_ */
