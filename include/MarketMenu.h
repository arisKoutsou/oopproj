// MarketMenu.h --- 
// 
// Filename: MarketMenu.h
// Author: George Liontos
// Created: Fri Dec 29 00:33:06 2017 (+0200)

#if !defined(__MARKET_MENU_HEADER__)
#define __MARKET_MENU_HEADER__

#include <iostream>
#include "Menu.h"
#include "../market/Market.h"

using namespace std;

class MarketMenu : public Menu {
public:
  MarketMenu(Market& market);
  ~MarketMenu();
  void handleSelection(int option);
private:
  Market market;
};

#endif
