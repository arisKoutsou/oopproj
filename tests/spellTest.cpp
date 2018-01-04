/*
 * Spell_test.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */
#include <iostream>

#include "../include/Spell.h"
#include "../include/IceSpell.h"
#include "../include/FireSpell.h"
#include "../include/LightningSpell.h"

using namespace std;

int main(int argc, char **argv) {

	Spell* spell = new LightningSpell("Fireball");
	cout << spell->getInfo();
	//cout << spell->getMagicPowerRequired();
	delete spell;
	return 0;
}
