/*
 * Spirit.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Spirit.h"

Spirit::Spirit(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg        
) : Monster(gr, y, x, nam, hp, min, max, arm, dodg+dodgeBonus),
    dodgeBonus(0.1)
{

}


