/*
 * Armor.h
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */

#ifndef ITEMS_ARMOR_H_
#define ITEMS_ARMOR_H_

#include "Item.h"

class Armor: public Item {
public:
	Armor(
		string name,
		int val = 25,
		int s = 15,
		int minL = 3,
		double reduce = 0.1	// if he takes 100 damages, he really takes 90.
	);
	virtual ~Armor();

	double getDamageReductionFactor() const;	// Returns private member.
	string getInfo() const;	// Uses base ...

private:
	double reduceDamageTakenBy;	// A double in [0, 1],
								// Representing percentage of reduced damage.
};

#endif /* ITEMS_ARMOR_H_ */
