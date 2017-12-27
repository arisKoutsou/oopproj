/*
 * Random.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: aris
 */

#include "Random.h"

Random::Random() {

}

double Random::from0to1() {

	return (double)rand() / RAND_MAX;
}

bool Random::boolean(const double p) {

	return (Random::from0to1() < p) ? true : false;
}

unsigned int Random::from0toMax(const unsigned int max) {

	return rand() % (max + 1);
}

int Random::fromMintoMax(const int min, const int max) {
	return from0toMax(max-min) + min;
}