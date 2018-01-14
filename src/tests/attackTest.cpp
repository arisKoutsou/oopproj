/*
 * attackTest.cpp
 *
 *  Created on: Jan 14, 2018
 *      Author: aris
 */


#include <iostream>
#include <cstdlib>

#include "../grid/Grid.h"
#include "../livings/heroes/Warrior.h"	// Use a kindOf Hero...
#include "../livings/heroes/Paladin.h"	// Use a kindOf Hero...
#include "../livings/monsters/Spirit.h"	// Use a kindOf Monster...
//#include "../market/Market.h"			// Put a market maybe...
#include "../random/Random.h"			// Use random boolean.
#include "../exceptions/heroExceptions.h"
#include "../items/Item.h"
#include "../items/Weapon.h"

int main() {

	Hero* warrior = new Warrior(NULL, 0, 0, "Hercules");
	Hero* paladin = new Paladin(NULL, 0, 0, "Cavalry");
	Monster* monster = new Spirit(NULL, 0, 0, "Snake");

	cout << "Printing hero stats..." << endl;
	warrior->printStats();
	paladin->printStats();
	cout << "Printing monster stats..." << endl;
	monster->printStats();

	warrior->attack(monster);
	paladin->attack(monster);
	monster->attack(warrior);
	monster->attack(paladin);

	cout << "Printing hero stats..." << endl;
	warrior->printStats();
	paladin->printStats();
	cout << "Printing monster stats..." << endl;
	monster->printStats();

	return EXIT_SUCCESS;
}
