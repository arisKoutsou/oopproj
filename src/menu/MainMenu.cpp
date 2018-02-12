/*
 * MainMenu.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: aris
 */

#include <iostream>

#include "MainMenu.h"

using namespace std;

MainMenu::MainMenu(vector<string>& opt) {
	for (size_t i = 0; i < opt.size(); i++) {
		options.push_back(opt[i]);
	}
}

MainMenu::MainMenu() {
	options.push_back("Play");
	options.push_back("GenerateMap");
	options.push_back("Help");
	options.push_back("Quit");
}

void MainMenu::welcome() const {

	cout << endl;
	cout << "+---+---+---+---+" << endl;
	cout << "| R | o | l | e |" << 	endl;
	cout << "+---+---+---+---+---+---+---+---+" << endl;
	cout << "    | P | l | a | y | i | n | g |" << endl;
	cout << "    +---+---+---+---+---+---+---+" << endl;
	cout << "        | G | a | m | e |"			<< endl;
	cout << "        +---+---+---+---+"			<< endl;
	cout << endl;

	print();

	cout << endl
	<< "Type any of the above options to enter (i.e : \"GenerateMap\" or \"Help\")"
	<< endl << endl;
}

void MainMenu::print() const {

	for (size_t i = 0; i < options.size(); i++) {
		cout << options[i] << endl;
	}
}

string MainMenu::prompt() const {
	string userInput;

	cout << "> ";
	cin >> userInput;

	for (size_t i = 0; i < options.size(); i++) {
		if (userInput == options[i]) {
			return userInput;
		}
	}

	cout << "Your input does not match any option." << endl << endl;
	return prompt();
}
