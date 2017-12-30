/*
 * Spell_test.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */
#include <iostream>

#include "../src/spells/Spell.h"
#include "../src/spells/IceSpell.h"
#include "../src/spells/FireSpell.h"
#include "../src/spells/LightningSpell.h"

using namespace std;

int main(int argc, char **argv) {

	Spell* spell = new LightningSpell("Fireball");
	cout << spell->getInfo();
	//cout << spell->getMagicPowerRequired();
	delete spell;
	return 0;
}
