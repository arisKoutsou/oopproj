/*
 * Spirit.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_SPIRIT_H_
#define LIVINGS_SPIRIT_H_

#include "../Monster.h"

class Spirit: public Monster {
public:
	Spirit(
		string nam,
		int hp = 500,
		int min = 10,
		int max = 20,
		int arm = 5,
		double dodg = 0.1
	);

private:
	const int dodgeBonus = 0.1;
};

#endif /* LIVINGS_SPIRIT_H_ */
