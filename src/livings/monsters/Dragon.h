/*
 * Dragon.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_DRAGON_H_
#define LIVINGS_DRAGON_H_

#include "../Monster.h"

class Grid;

class Dragon: public Monster {
public:
	Dragon(
	        Grid* gr,
		int y = 0,
		int x = 0,
		string nam = "",
		int hp = 500,
		int min = 10,
		int max = 20,
		int arm = 5,
		double dodg = 0.1
	);

private:
        const int damageBonus;

};

#endif /* LIVINGS_DRAGON_H_ */
