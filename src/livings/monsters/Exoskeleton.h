/*
 * Exoskeleton.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_EXOSKELETON_H_
#define LIVINGS_EXOSKELETON_H_

#include "../Monster.h"

class Exoskeleton: public Monster {
public:
	Exoskeleton(
		string nam,
		int hp = 500,
		int min = 10,
		int max = 20,
		int arm = 5,
		double dodg = 0.1,
		int x = 0,
		int y = 0
	);

private:
	const int armorBonus = 10;

};

#endif /* LIVINGS_EXOSKELETON_H_ */
