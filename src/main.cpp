#include <iostream>
#include <cstdlib>

#include "items/Item.h"

using namespace std;

int main(int argc, char* argv[]) {
	Item item("sword");
	cout << item.getInfo();
 	return EXIT_SUCCESS;
}
