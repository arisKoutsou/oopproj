/*
 * Dragon.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_DRAGON_H_
#define LIVINGS_DRAGON_H_

#include "../Monster.h"

class Dragon: public Monster {
public:
	Dragon(
		string nam,
		int hp = 500,
		int min = 10,
		int max = 20,
		int arm = 5,
		double dodg = 0.1,
		int x = 0,
		int y = 0
	);

private:
	const int damageBonus = 5;

};

#endif /* LIVINGS_DRAGON_H_ */
