/*
 * heroOnGridTest.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: aris
 */
#include <iostream>
#include <cstdlib>

#include "../grid/Grid.h"
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

	/* Simple array.
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
	*/

	// Random array.
	Random random;
	int rows = 10, columns = 15;
	bool* randomTileInfo = new bool[rows*columns*2];	// 10 rows, 15 columns.
	for (int i = 0; i < rows*columns*2; ) {
		// odd index, so nonAccesible info.
		randomTileInfo[i] = random.boolean(0.1);
		randomTileInfo[i+1] = !randomTileInfo[i];
		i+=2;
	}

	// Creating a grid, on which heroes will move.
	// This grid is based on the tileInfo array,
	// Which gives the information about nonAccessible Tiles.
	Grid grid(
		columns,	// m columns.
		rows,	// n lines.
		randomTileInfo	// Previously made bool[].
	);

	// Create a Market and insert it on the grid.
	// Market MUST BE of type <Market*>.
	Market* market1 = new Market(10);	// maxCapacity of market1 is 10.
	grid.addMarket(1, 3, market1);		// Add a market at the 2nd row, 4th column.

	// Νow add a Hero on the grid.
	Hero* warrior = new Warrior(
		&grid,			// This warrior lives on the previously made grid.
		2, 0,			// Put him on the 1st row, 3rd column.
		"Tryndamere"	// Name.
		// Rest of the arguments to constructor default...
	);
	
	grid.print();
	try {
	  warrior->move(Hero::DOWN);
	}
	catch (HeroMoveException& e) {
	  cout << e.what() << endl;
	}

	grid.print();
	
	Item* sword = new Weapon("Excalibur");

	warrior->getInventory().addItem(sword);

	warrior->printStats();
	
	warrior->checkInventory();

	warrior->printStats();
	
	delete[] randomTileInfo;
	return EXIT_SUCCESS;
}


