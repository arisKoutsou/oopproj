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
	double arm,
	double dodg,
	int _damageBonus
) :  damageBonus(_damageBonus),
     Monster(gr, y, x, nam, hp, min, max, arm, dodg) {

  minDamage += damageBonus;
  maxDamage += damageBonus;
}
