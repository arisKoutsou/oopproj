/*
 * ------------------------- Random.h
 *
 *  Created on: Nov 25, 2017
 *      Author: aris
 */

#ifndef RANDOM_RANDOM_H_
#define RANDOM_RANDOM_H_

#include <cstdlib>
#include <ctime>

class Random {

public:
        explicit Random(int seed = 0);		// Initialize seed.

	static double from0to1();
	static bool boolean(const double p = 0.5);						// returns true with probability p.
	static unsigned int from0toMax(const unsigned int max);	// Random from [0, max].
	static int fromMintoMax(const int min, const int max);
};

#endif /* RANDOM_RANDOM_H_ */
