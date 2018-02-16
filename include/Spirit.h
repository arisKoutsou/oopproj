/*
 * Spirit.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_SPIRIT_H_
#define LIVINGS_SPIRIT_H_

#include "Monster.h"

class Grid;

class Spirit: public Monster {
public:
	Spirit(
	        Grid* gr,
		int y = 0,
		int x = 0,
		string nam = "",
		int hp = 500,
		int min = 10,
		int max = 20,
		double arm = 0.1,
		double dodg = 0.1,
		double dodgeBonus = 0.1
	);

private:
        const double dodgeBonus;
};

#endif /* LIVINGS_SPIRIT_H_ */
