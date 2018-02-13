/*
 * Potion.h
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */

#ifndef ITEMS_POTION_H_
#define ITEMS_POTION_H_

#include "Item.h"

class Potion: public Item {
public:
	Potion(
		string name,
		int val = 25,
		int s = 15,
		int minL = 3,
		double sB = 0.1,
		double dB = 0.0,
		double aB = 0.05,
		int rounds = 2
	);
	~Potion();

	double getAgilityBoost() const;
	double getDexterityBoost() const;
	double getStrengthBoost() const;
	int getRoundsEffective() const;
        void getInfo() const;
        string kindOf() const;
	bool operator==(const Potion& rValue) const;
	void roundPassed();
private:
	// All boosts are doubles in [0,1] and that means.
	// That they will boost damage to damage*(1+boostAmount)...
	// i.e if damage = 100, and strength boost = 0.1
	// new damage is 110.
	double strengthBoost;
	double dexterityBoost;
	double agilityBoost;
	int roundsEffective;

};

#endif /* ITEMS_POTION_H_ */
