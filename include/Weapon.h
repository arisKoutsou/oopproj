/*
 * Weapon.h
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */

#ifndef ITEMS_WEAPON_H_
#define ITEMS_WEAPON_H_

#include "Item.h"

class Weapon : public Item {
public:
	Weapon(
		string name,
		int val = 25,
		int s = 15,
		int minL = 3,
		int dmg = 80,
		bool both = false
	);
	~Weapon();

        void getInfo() const;
	int getDamage() const;	// How much damage it has.
        
        bool needsBothHands() const;
        string kindOf() const;
        bool operator==(const Weapon& rValue) const;
private:
	int damage;				// Damage done when used.
	bool requiresBothHands;	// True if this Weapon requires both hands.
};

#endif /* ITEMS_WEAPON_H_ */
