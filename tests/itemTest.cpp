/*
 * test.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */

#include <iostream>

#include "../src/items/Item.h"
#include "../src/items/Weapon.h"
#include "../src/items/Armor.h"
#include "../src/items/Potion.h"
#include "../src/random/Random.h"

int main() {

	// Testing Item...
	Item* item = new Item("Boots");
	cout << item->getInfo();
	delete item;

	// Testing Weapon...
	Item* weapon = new Weapon("Sword");
	cout << weapon->getInfo();
	delete weapon;

	// Testing Armor...
	Item* armor = new Armor("Shield");
	cout << armor->getInfo();
	delete armor;

	// Testing Potion...
	Item* potion = new Potion("manaPotion");
	cout << potion->getInfo() << endl;
	delete potion;

	Random random;

	cout << random.from0to1();

	return 0;
}

