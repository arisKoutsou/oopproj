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
  virtual ~Menu();

  int getNumberOfOptions() const; // Returns the number of options
  void displayMenu() const;	  // Displays the menu
  void setMenuOption();	 // Sets a new option for the menu
  void clearMenu() const;	// Clears the menu screen
  int getSelection();   // Returns the selection the user made

  // Handles the selection of the user
  virtual void handleSelection(int option) = 0;
private:
  vector<string> options;
};

#endif
