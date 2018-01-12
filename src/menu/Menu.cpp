// Menu.cpp --- 
// 
// Filename: Menu.cpp
// Author: George Liontos
// Created: Fri Dec 29 00:01:55 2017 (+0200)

#include <iostream>
#include "./Menu.h"

using namespace std;

Menu :: Menu(const Market& market) {
  this->options.push_back("Display Market Items/Spells");
  this->options.push_back("Buy Item/Spell");
  this->options.push_back("Sell Item/Spell");
  this->options.push_back("Exit Market");
}

Menu :: Menu(const Inventory& inventory) {
  this->options.push_back("Display inventory");
  this->options.push_back("Equip Item/Spell");
  this->options.push_back("Discard Item/Spell");
  this->options.push_back("Use Potion");
  this->options.push_back("Exit Inventory");
}

Menu :: ~Menu() {}

int Menu :: getNumberOfOptions() const {
  return (options.size());
}

void Menu :: displayMenu() const {
  for (size_t i = 0; i != options.size(); ++i) {
    cout << i + 1 << ". " << options[i] << endl;
  }
  cout << endl;
}

void Menu :: clearMenu() const {
  // Yes I know, that way is pathetic... :)
  //cout << string(100, '\n');	// Can't debug... removed temporarily.
}

int Menu :: getSelection() {
  int option;

  do {
    cout << "Please enter an option: ";
    cin >> option;
  } while (option < 1 && option > options.size());
  
  return option;
}
