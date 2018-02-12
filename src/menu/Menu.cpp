// Menu.cpp --- 
// 
// Filename: Menu.cpp
// Author: George Liontos
// Created: Fri Dec 29 00:01:55 2017 (+0200)

#include <iostream>
#include <limits>
#include "Menu.h"

using namespace std;

Menu :: Menu() {}

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
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize> :: max(), '\n');
    }
  } while (option < 1 && option > options.size());  
  return option;
}
