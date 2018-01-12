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

class Monster: public Living {
public:
	Monster(
		Grid* gr,
		int y = 0,
		int x = 0,
		string nam = "",
		int hp = 500,
		int min = 10,
		int max = 20,
		int arm = 5,
		double dodg = 0.1                
	);
	int getArmor() const;
	double getDodge() const;
	int getMaxDamage() const;
	int getMinDamage() const;
protected:
       Grid* grid;  
private:
	int minDamage;
	int maxDamage;
	int armor;		// Reduce damage taken.
	double dodge;	// Probabillity for dodge.

};

#endif /* LIVINGS_MONSTER_H_ */
