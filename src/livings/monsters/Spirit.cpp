/*
 * Spirit.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Spirit.h"

Spirit::Spirit(
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg,
	int x,
	int y
) : Monster(nam, hp, min, max, arm, dodg+dodgeBonus, x, y){

}


