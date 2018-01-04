/*
 * test.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: aris
 */

#include <iostream>

#include "../include/Item.h"
#include "../include/Weapon.h"
#include "../include/Armor.h"
#include "../include/Potion.h"
#include "../include/Random.h"

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

