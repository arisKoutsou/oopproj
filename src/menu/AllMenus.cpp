#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

#include "../../include/AllMenus.h"

using namespace std;

BasicMenu :: BasicMenu()
  : Menu() {
  options.push_back("Display stats");
  options.push_back("Check invnentory");
  options.push_back("Move");
  options.push_back("Go to Main Menu");
}

BattleMenu :: BattleMenu()
  : Menu() {
  options.push_back("Display stats");
  options.push_back("Attack");
  options.push_back("Cast spell");
  options.push_back("Use potion");
  options.push_back("Change weapon/armor");
  options.push_back("Go to Main Menu");
}

MarketMenu :: MarketMenu()
  : Menu() {
  options.push_back("Display Items/Spells");
  options.push_back("Buy Item/Spell");
  options.push_back("Sell Item/Spell");
  options.push_back("Exit Market");
  options.push_back("Go to Main Menu");
}

InventoryMenu :: InventoryMenu()
  : Menu() {
  options.push_back("Display Items/Spells");
  options.push_back("Equip Item/Spell");
  options.push_back("Discard Item/Spell");
  options.push_back("Use Potion");
  options.push_back("Exit Inventory");
  options.push_back("Go to Main Menu");
}

MainMenu :: MainMenu()
  : Menu() {
  options.push_back("Play");
  options.push_back("GenerateMap");
  options.push_back("Help");
  options.push_back("Quit");
}

void MainMenu :: welcome() const {  
  cout << endl << "Welcome to ..." << endl;

  displayMenu();

  cout << "Type any of the above options to enter (i.e : \"GenerateMap\" or \"Help\")"
       << endl << endl;
}

string MainMenu :: prompt() const {
  string userInput;

  cout << "> ";
  cin >> userInput;
  transform(userInput.begin(), userInput.end(),
	    userInput.begin(), :: tolower);  
  for (size_t i = 0; i < options.size(); i++) {
    string tmp = options[i];
    transform(tmp.begin(), tmp.end(), tmp.begin(), :: tolower);
    if (userInput == tmp) {
      return userInput;
    }
  }

  cout << endl << "Your input does not match any option." << endl << endl;
  return prompt();
}

void MainMenu :: displayMenu() const {

  cout << endl;
  cout << "+---+---+---+---+"                 << endl;
  cout << "| R | o | l | e |"                 << endl;
  cout << "+---+---+---+---+---+---+---+---+" << endl;
  cout << "    | P | l | a | y | i | n | g |" << endl;
  cout << "    +---+---+---+---+---+---+---+" << endl;
  cout << "        | G | a | m | e |"         << endl;
  cout << "        +---+---+---+---+"	      << endl;
  cout << endl;

  for (size_t i = 0; i != options.size(); ++i) {
    cout << "•" << options[i] << endl;
  }
  cout << endl;
}

void MainMenu::help() const {
	ifstream helpFile;

	helpFile.open("input/help.info");

	if (helpFile.is_open()) {
		cout << endl;
		cout << helpFile.rdbuf();
	} else {
		cerr << "A problem occured while opening \"input/help.info\" ";
		cout << endl<< endl;
	}

	string answer;
	  while (answer != "Y" && answer != "y") {
		cout << endl << "Exit to Main Menu?(Y/n) : ";
		cin >> answer;
	  }
}


