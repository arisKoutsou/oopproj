/*
 * Exoskeleton.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "../../../include/Exoskeleton.h"

Exoskeleton::Exoskeleton(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp,
	int min,
	int max,
	double arm,
	double dodg,
	double _armorBonus
) : armorBonus(_armorBonus),
	Monster(gr, y, x, nam, hp, min, max, arm, dodg) {

  damageReductionFactor += armorBonus;
}
