/*
 * Monster.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_MONSTER_H_
#define LIVINGS_MONSTER_H_

#include "./Living.h"

class Grid;
class Hero;

class Monster: public Living {
public:
	Monster(
		Grid* gr,
		int y,
		int x,
		string nam,
		int hp = 500,
		int min = 10,
		int max = 20,
		int arm = 0.1,
		double dodg = 0.1                
	);

	int getDamageReductionFactor() const;
	double getDodge() const;
	int getMaxDamage() const;
	int getMinDamage() const;
        string kindOf() const;
        void printStats() const;
        void receiveDamage(int damageDealt);// Reduces health by damageDealt.
        void attack(Hero* hero);			// Reduces hero's health.
private:
	int minDamage;
	int maxDamage;
	double damageReductionFactor;	// Reduce damage taken.
	double dodge;	// Probabillity for dodge.

};

#endif /* LIVINGS_MONSTER_H_ */
