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
) :  damageBonus(5),
     Monster(gr, y, x, nam, hp, min + 5, max + 5, arm, dodg)
{

}
