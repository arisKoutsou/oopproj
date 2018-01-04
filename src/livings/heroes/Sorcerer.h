/*
 * Sorcerer.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_SORCERER_H_
#define LIVINGS_SORCERER_H_

#include "../Hero.h"

class Sorcerer: public Hero {
	// This type of hero is better at:
	// Agility, Dexterity.
	// At level up these characteristics
	// Get an extra bonus...
	public:
		Sorcerer(
			string nam,
			int hp = 500,
			int mp = 200,
			int s = 100,
			int a = 250,
			int d = 100
		);
		void levelUp();	// Increase stats.

	private:
		const double agilityBonus = 0.1;
		const double dexterityBonus = 0.1;
};

#endif /* LIVINGS_SORCERER_H_ */
