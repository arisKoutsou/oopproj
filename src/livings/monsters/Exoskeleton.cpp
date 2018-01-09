/*
 * Exoskeleton.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Exoskeleton.h"

Exoskeleton::Exoskeleton(
	Grid* gr,
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg,
	int x,
	int y
) : Monster(gr, nam, hp, min, max, arm+armorBonus, dodg, x, y),
    armorBonus(10)
{

}
