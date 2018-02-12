#include "game_utils.h"
#include "menu/MainMenu.h"

int main(int argc, char* argv[]) {

	MainMenu mainMenu;	// Create the default menu.
	string userInput;

	while (userInput != "Quit") {
		mainMenu.welcome();	// Print silly title...

		userInput = mainMenu.prompt();	// Get userInput.

		if (userInput == "Play") {
			run(argc, argv);
		} else if (userInput == "GenerateMap") {
			generateMap();
		} else if (userInput == "Help") {
//			mainMenu.help();
		}
	}

	cout << endl
	<< "Exiting game..." << endl;

	return EXIT_SUCCESS;
}
