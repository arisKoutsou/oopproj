/*
 * FireSpell.h
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#ifndef SPELLS_FIRESPELL_H_
#define SPELLS_FIRESPELL_H_

#include "Spell.h"

class FireSpell: public Spell {
public:
	FireSpell(
		string 	nam,
		int 	val = 20,
		int 	minL = 1,
		int 	magicP = 10,
		int		minDmg = 80,
		int 	maxDmg = 100,
		double  reduction = 0.1,	// new data member.
		int 	rounds = 3
	);

	// Returns double in [0, 1].
	// The percentage which enemy damage will be reduced.
	double reduceOponentArmorBy() const;
	int    getReductionRounds() const;
	string getInfo() const;

        // Added by: (George Liontos)
        bool operator==(const FireSpell& rValue) const;
private:
	double 	oponentArmorReduction;
	int 	rounds;
};

#endif /* SPELLS_FIRESPELL_H_ */
