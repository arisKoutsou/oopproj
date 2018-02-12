#if !defined(__ALL_MENUS_HEADER__)
#define __ALL_MENUS_HEADER__

#include <iostream>

using namespace std;

#include "Menu.h"

class MarketMenu : public Menu {
public:
  MarketMenu();
};

class BasicMenu : public Menu {
public:
  BasicMenu();
};

class BattleMenu : public Menu {
public:
  BattleMenu();
};

class InventoryMenu : public Menu {
public:
  InventoryMenu();
};

class MainMenu : public Menu {
public:
  MainMenu();  // Initial print of the menu when starting game.
  void welcome() const;
  string prompt() const; // Promts for user input and returns the selection.
  void displayMenu() const;
};

#endif
