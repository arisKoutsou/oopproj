/*
 * Dragon.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Dragon.h"

Dragon::Dragon(
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg,
	int x,
	int y
) : Monster(nam, hp, min+damageBonus, max+damageBonus, arm, dodg, x, y){

}


