/*
 * MainMenu.h
 *
 *  Created on: Feb 12, 2018
 *      Author: aris
 *
 * 	This is the main menu of the game.
 * 	It appears when the game starts,
 * 	and when game is over and exiting the app
 * 	is needed.
 */

#ifndef SRC_MENU_MAINMENU_H_
#define SRC_MENU_MAINMENU_H_

#include "string"
#include "vector"

using namespace std;

class MainMenu {
public:
	MainMenu(vector<string>& opt);
	MainMenu();

	void welcome() const;	// Initial print of the menu when starting game.
	void print() const;		// Prints only the options.
	string prompt() const;	// Promts for user input and returns the selection.

private:
	vector<string> options;
};

#endif /* SRC_MENU_MAINMENU_H_ */
