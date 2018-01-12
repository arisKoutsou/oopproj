/*
 * Dragon.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Dragon.h"

Dragon::Dragon(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg        
) : Monster(gr, y, x, nam, hp, min+damageBonus, max+damageBonus, arm, dodg),
    damageBonus(5)
{

}


