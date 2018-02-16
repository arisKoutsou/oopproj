/*
 * Monster.h
 *
 *  Created on: Jan 4, 2018
 *      Author: aris
 */

#ifndef LIVINGS_MONSTER_H_
#define LIVINGS_MONSTER_H_

#include <list>

#include "Living.h"

class Grid;
class Hero;

class Monster: public Living {
public:
        typedef enum {
	  FIRE, ICE, LIGHT
	} Type;
  
        struct Nerf {
	private:
	  int duration;
	  double nerfAmount;
	  Type nerfType;
	public:
	  Nerf(int duration, double nerfAmount, Type nerfType);
	  int getDuration() const;
	  double getNerfAmount() const;
	  Type getNerfType() const;
	  void roundPassed();
	};

        Monster(
		Grid* gr,
		int y,
		int x,
		string nam,
		int hp = 500,
		int min = 10,
		int max = 20,
		double arm = 0.1,
		double dodg = 0.1                
	);

        void setLevel(int level);
        double getDamageReductionFactor() const;
	double getDodge() const;
	int getMaxDamage() const;
	int getMinDamage() const;
        string kindOf() const;
        void printStats() const;
        void receiveDamage(int damageDealt);// Reduces health by damageDealt.
        void attack(Hero* hero);			// Reduces hero's health.
        void applyNerf(int duration, double amount, Type nerfType); // Applies a new nerf to the monster
        void updateNerfs();
protected:
	int minDamage;
	int maxDamage;
	double damageReductionFactor;	// Reduce damage taken.
	double dodge;	// Probabillity for dodge.
        list<Nerf> nerfs;
};

#endif /* LIVINGS_MONSTER_H_ */
