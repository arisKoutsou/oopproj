// InventoryMenu.h --- 
// 
// Filename: InventoryMenu.h
// Author: George Liontos
// Created: Fri Dec 29 13:06:37 2017 (+0200)

#if !defined(__INVENTORY_MENU_HEADER__)
#define __INVENTORY_MENU_HEADER__

#include <iostream>
#include "Menu.h"

class Inventory;

using namespace std;

class InventoryMenu : public Menu {
public:
  InventoryMenu();
  ~InventoryMenu();
};

#endif
