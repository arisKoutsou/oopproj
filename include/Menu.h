// Menu.h --- 
// 
// Filename: Menu.h
// Author: George Liontos
// Created: Fri Dec 29 00:01:50 2017 (+0200)

#if !defined(__MENU_HEADER__)
#define __MENU_HEADER__

#include <iostream>
#include <vector>

using namespace std;

class Menu {
public:
  Menu();
  ~Menu();

  int getNumberOfOptions() const; // Returns the number of options
  void displayMenu() const;	  // Displays the menu
  void setMenuOption(const string& option); // Sets a new option for the menu
  void clearMenu() const;	// Clears the menu screen
  int getSelection();   // Returns the selection the user made
private:
  vector<string> options;
};

#endif
