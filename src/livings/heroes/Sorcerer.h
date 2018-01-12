/*
 * Sorcerer.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_SORCERER_H_
#define LIVINGS_SORCERER_H_

#include "../Hero.h"

class Grid;

class Sorcerer: public Hero {
	// This type of hero is better at:
	// Agility, Dexterity.
	// At level up these characteristics
	// Get an extra bonus...
	public:
		Sorcerer(
			Grid* gr,
			int y = 0,
			int x = 0,
			string nam = "",
			int hp = 500,
			int mp = 200,
			int s = 100,
			int a = 250,
			int d = 100
		);
		void levelUp();	// Increase stats.

        // Added by: (George Liontos)
        bool operator==(const Sorcerer& rValue) const;
	private:
		const double agilityBonus;
		const double dexterityBonus;
};

#endif /* LIVINGS_SORCERER_H_ */
