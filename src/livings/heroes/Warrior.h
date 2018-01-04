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

private:
	const double agilityBonus = 0.1;
	const double strengthBonus = 0.1;
};

#endif /* LIVINGS_WARRIOR_H_ */
