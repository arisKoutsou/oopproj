/*
 * Paladin.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_PALADIN_H_
#define LIVINGS_PALADIN_H_

#include "../Hero.h"

class Grid;

class Paladin: public Hero {
	// This type of hero is better at:
	// Strength, Dexterity.
	// At level up these characteristics
	// Get an extra bonus...
	public:
		Paladin(
			Grid* gr,
			int x,
			int y,
			string nam,
			int hp = 500,
			int mp = 200,
			int s = 100,
			int a = 250,
			int d = 100
		);
		void levelUp();	// Increase stats.

        // Added by: (George Liontos)
        bool operator==(const Paladin& rValue) const;

        private:
		const double strengthBonus;
		const double dexterityBonus;
};

#endif /* LIVINGS_PALADIN_H_ */
