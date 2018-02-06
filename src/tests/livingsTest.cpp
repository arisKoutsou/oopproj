/*
 * livingsTest.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: aris
 */
#include <iostream>
#include <cstdlib>

#include "../grid/Grid.h"
#include "../livings/Living.h"
#include "../livings/heroes/Warrior.h"	// Use a kindOf Hero...
#include "../market/Market.h"			// Put a market maybe...
#include "../random/Random.h"			// Use random boolean.
#include "../exceptions/heroExceptions.h"
#include "../items/Item.h"
#include "../items/Weapon.h"

int main() {

	// Array of bools.
	// Each pair of bools in the array represents
	// even index represents bool info "nonAccessible".
	// odd index represents bool info "common"
	// i.e : 1010
	// represents a grid that it's 2 tiles by ascending order,
	// are : 1(nonAccessible, )
	// Creating array of bool info...

	// Simple array.
	bool tileInfo[32] =		// Size of array MUST BE: <rows*columns*2>
	{
		true, false, // <nonAccessible>, <common>,
		false, true,
		false, true,
		false, true,
		false, true,
		false, true,
		false, true,
		false, true,
		true, false,
		false, true,
		false, true,
		false, true,
		false, true,
		false, true,
		false, true,
		true, false
	};

	// Creating a grid, on which heroes will move.
	// This grid is based on the tileInfo array,
	// Which gives the information about nonAccessible Tiles.
	Grid grid(
		4,	// m columns.
		4,	// n lines.
		tileInfo	// Previously made bool[].
	);

	Hero* heroP = new Warrior(&grid, 0, 3, "Teemo");

	heroP->printStats();
	cout << "Leveling up..." << endl << endl;
	heroP->levelUp();
	heroP->printStats();

	grid.displayMap();

	cout << "Moving up" << endl << endl ;
	heroP->move(Hero::UP);

	grid.displayMap();

	return EXIT_SUCCESS;
}

