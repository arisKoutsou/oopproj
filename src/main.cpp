/*
 * main.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: aris
 */

#include <iostream>

#include "items/Item.h"

using namespace std;

int main() {
	Item item("sword");
	cout << item.getInfo();
	return 0;
}


