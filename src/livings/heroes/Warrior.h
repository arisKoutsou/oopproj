/*
 * Warrior.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_WARRIOR_H_
#define LIVINGS_WARRIOR_H_

#include "../Hero.h"

class Warrior: public Hero {
	// This type of hero is better at:
	// Agility, Strength.
	// At level up these characteristics
	// Get an extra bonus...
public:
	Warrior(
		string nam,
		int hp = 500,
		int mp = 200,
		int s = 100,
		int a = 250,
		int d = 100
	);
	void levelUp();	// Increase stats.

        // Added by: (George Liontos)
        bool operator==(const Warrior& rValue) const;
  
private:
	const double agilityBonus;
        const double strengthBonus;
};

#endif /* LIVINGS_WARRIOR_H_ */
