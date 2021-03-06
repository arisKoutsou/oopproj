/*
 * Spell.h
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */

#ifndef SPELLS_SPELL_H_
#define SPELLS_SPELL_H_

#include <string>

using namespace std;

class Spell {
public:
	Spell(
		string 	nam,
		int 	val = 20,
		int 	minL = 1,
		int 	magicP = 10,
		int	minDmg = 80,
		int 	maxDmg = 100
	);
	virtual ~Spell();

	int getMagicPowerRequired() const;
	int getMaxDamage() const;
	int getMinDamage() const;
	int getMinLevel() const;
	const string& getName() const;
	int getValue() const;
	int sellsFor() const;

        virtual void getInfo() const;
        virtual const string kindOf() const = 0;
        virtual bool operator==(const Spell& rValue) const;
        const double sellRate;
private:
	string 	name;
	int 	value;
	int 	minLevel;
	int 	magicPowerRequired;

	int minDamage;
	int maxDamage;

};

#endif /* SPELLS_SPELL_H_ */
