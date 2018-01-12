/*
 * Exoskeleton.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Exoskeleton.h"

Exoskeleton::Exoskeleton(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg        
) : Monster(gr, y, x, nam, hp, min, max, arm+armorBonus, dodg),
    armorBonus(10)
{

}
