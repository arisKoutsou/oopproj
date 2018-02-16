/*
 * LightningSpell.h
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#ifndef SPELLS_LIGHTNINGSPELL_H_
#define SPELLS_LIGHTNINGSPELL_H_

#include "Spell.h"

class LightningSpell: public Spell {
public:
	LightningSpell(
		string 	nam,
		int 	val = 20,
		int 	minL = 1,
		int 	magicP = 10,
		int	minDmg = 80,
		int 	maxDmg = 100,
		double  reduction = 0.23,
		int 	rounds = 1
	);

	// Returns double in [0, 1].
	// The percentage which enemy damage will be reduced.
	double reduceOponentDodgeBy() const;
	int    getReductionRounds() const;
        void getInfo() const;

        const string kindOf() const;
        bool operator==(const LightningSpell& rValue) const;
private:
	double 	oponentDodgeReduction;	// Decreases the possibility that an opponent dodges.
	int 	rounds;
};

#endif /* SPELLS_LIGHTNINGSPELL_H_ */
