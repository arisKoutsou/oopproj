/*
 * Exoskeleton.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#include "Exoskeleton.h"

Exoskeleton::Exoskeleton(
	string nam,
	int hp,
	int min,
	int max,
	int arm,
	double dodg
) : Monster(nam, hp, min, max, arm+armorBonus, dodg){

}
