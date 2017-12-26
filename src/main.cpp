#include <iostream>
#include <cstdlib>

#include "items/Item.h"

using namespace std;

int main(int argc, char* argv[]) {
	Item item("sword");
	cout << item.getInfo();
	// etsi einai kalo na ta ektypwnei sto menou argotera ?
	// opou 8a agorazeis items kai kala ...
 	return EXIT_SUCCESS;
}
