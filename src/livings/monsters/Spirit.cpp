/*
 * Spirit.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Spirit.h"

Spirit::Spirit(
	Grid* gr,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg,
	int x,
	int y
) : Monster(gr, nam, hp, min, max, arm, dodg+dodgeBonus, x, y){

}


