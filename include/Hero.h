/*
 * Hero.h
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#ifndef LIVINGS_HERO_H_
#define LIVINGS_HERO_H_

#include "Living.h"
#include "Inventory.h"

class Hero : public Living {
public:
	Hero(
		string nam,
		int hp = 500,
		int mp = 200,
		int s = 100,
		int a = 250,
		int d = 100
	);
	int getAgility() const;
	int getDexterity() const;
	int getExpirience() const;
	int getMagicPower() const;
	int getMoney() const;
	int getStrength() const;

private:
	int 	magicPower;	// Mana.
	int 	strength;
	int 	agility;
	int 	dexterity;
	int 	money;		// Gold.
	int 	expirience;	// Xp.

	Inventory inventory;	// Implemented by george.
                                // Contains all items and spells.

        // Added by: (George Liontos)
        bool operator==(const Hero& rValue) const;
};

#endif /* LIVINGS_HERO_H_ */
