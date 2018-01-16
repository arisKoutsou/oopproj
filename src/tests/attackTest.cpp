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
#include "../market/Market.h"			// Put a market maybe...
#include "../random/Random.h"			// Use random boolean.
#include "../exceptions/heroExceptions.h"
#include "../items/Item.h"
#include "../items/Weapon.h"
#include "../items/Potion.h"

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

	grid.displayMap();

	Hero* warrior = new Warrior(&grid, 0, 2, "Hercules");
//	Hero* paladin = new Paladin(&grid, 0, 1, "Cavalry");
//	Monster* monster = new Spirit(&grid, 0, 1, "Snake");

//	// Attacking test... good.
//	cout << "Printing hero stats..." << endl;
//	warrior->printStats();
//	paladin->printStats();
//	cout << "Printing monster stats..." << endl;
//	monster->printStats();
//
//	warrior->attack(monster);
//	paladin->attack(monster);
//	monster->attack(warrior);
//	monster->attack(paladin);
//
//	cout << "Printing hero stats..." << endl;
//	warrior->printStats();
//	paladin->printStats();
//	cout << "Printing monster stats..." << endl;
//	monster->printStats();


	// Testing use (potion);
	Item* potion = new Potion("Elixir");	// Create a Potion.
	Market* market = new Market(1);			// A market.
	market->addItem(potion);				// Add the potion in the market.

	grid.addMarket(0, 2, market);	// Put the market where the hero is.
	grid.displayMap();

	//grid.addLiving(0, 2, warrior);
	cout << "Buying Elixir..." << endl;
	warrior->buy("Elixir");

	int round = 0;
	while(++round <= 5) {
		cout << "##### ROUND " << round << " ######"<< endl;
		warrior->printStats();
		warrior->checkInventory();
		warrior->nextRound();
	}

	return EXIT_SUCCESS;
}