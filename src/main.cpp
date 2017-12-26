#include <iostream>
#include <cstdlib>

#include "items/Item.h"
#include "random/Random.h"

using namespace std;

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Item item("sword");
	cout << item.getInfo() << endl;
	// etsi einai kalo na ta ektypwnei sto menou argotera ?
	// opou 8a agorazeis items kai kala ...

	// me pi8anotita 0.2 return false.
	cout << Random::boolean(0.0001) << endl;

	cout << Random::from0to1() << endl;
	cout << Random::fromMintoMax(-3, 3) << endl;

 	return EXIT_SUCCESS;
}
