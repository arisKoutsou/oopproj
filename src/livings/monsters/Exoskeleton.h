/*
 * Exoskeleton.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_EXOSKELETON_H_
#define LIVINGS_EXOSKELETON_H_

#include "../Monster.h"

class Grid;

class Exoskeleton: public Monster {
public:
	Exoskeleton(
		Grid* gr,
		int y = 0,
		int x = 0,
		string nam = "",
		int hp = 500,
		int min = 10,
		int max = 20,
		double arm = 0.1,
		double dodg = 0.1,
		double armorBonus = 0.15
	);

private:
	const int armorBonus;

};

#endif /* LIVINGS_EXOSKELETON_H_ */
