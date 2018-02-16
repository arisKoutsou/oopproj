/*
 * Spirit.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "../../../include/Spirit.h"

Spirit::Spirit(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int min,
	int max,
	double arm,
	double dodg,
	double _dodgeBonus
) : dodgeBonus(_dodgeBonus),
    Monster(gr, y, x, nam, hp, min, max, arm, dodg) {

  dodge += dodgeBonus;
}


