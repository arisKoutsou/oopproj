#include <iostream>
#include "AllMenus.h"

using namespace std;

BasicMenu :: BasicMenu()
  : Menu() {
  this->options.push_back("Display map");
  this->options.push_back("Display stats");
  this->options.push_back("Check invnentory");
  this->options.push_back("Move");
  this->options.push_back("Quit game");
}

BattleMenu :: BattleMenu()
  : Menu() {
  this->options.push_back("Display stats");
  this->options.push_back("Display all monsters stats");
  this->options.push_back("Attack");
  this->options.push_back("Cast spell");
  this->options.push_back("Use potion");
  this->options.push_back("Change weapon/armor");
  this->options.push_back("Quit game");
}

MarketMenu :: MarketMenu()
  : Menu() {
  this->options.push_back("Display Market Items/Spells");
  this->options.push_back("Buy Item/Spell");
  this->options.push_back("Sell Item/Spell");
  this->options.push_back("Exit Market");
  this->options.push_back("Quit game");
}

InventoryMenu :: InventoryMenu()
  : Menu() {
  this->options.push_back("Display inventory");
  this->options.push_back("Equip Item/Spell");
  this->options.push_back("Discard Item/Spell");
  this->options.push_back("Use Potion");
  this->options.push_back("Exit Inventory");
  this->options.push_back("Quit game");
}

// Added by Aris

MainMenu :: MainMenu()
  : Menu() {
  this->options.push_back("Play");
  this->options.push_back("GenerateMap");
  this->options.push_back("Help");
  this->options.push_back("Quit");
}

void MainMenu :: welcome() const {  
  cout << endl;
  cout << "+---+---+---+---+"                 << endl;
  cout << "| R | o | l | e |"                 << endl;
  cout << "+---+---+---+---+---+---+---+---+" << endl;
  cout << "    | P | l | a | y | i | n | g |" << endl;
  cout << "    +---+---+---+---+---+---+---+" << endl;
  cout << "        | G | a | m | e |"         << endl;
  cout << "        +---+---+---+---+"	      << endl;
  cout << endl;

  displayMenu();

  cout << endl
       << "Type any of the above options to enter (i.e : \"GenerateMap\" or \"Help\")"
       << endl << endl;
}

string MainMenu :: prompt() const {
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
