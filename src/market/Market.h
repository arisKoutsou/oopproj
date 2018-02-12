// Market.h --- 
// 
// Filename: Market.h
// Author: George Liontos
// Created: Wed Dec 27 16:29:34 2017 (+0200)

#if !defined(__MARKET_HEADER__)
#define __MARKET_HEADER__

#include <iostream>
#include <list>
#include "../menu/AllMenus.h"

class Item;
class Spell;

using namespace std;

class Market {
public:
  explicit Market(int maxCapacity = 20);
  ~Market();

  int getMaxCapacity() const;	// returns the max capacity of the market
  int getCurrentCapacity() const; // returns the current capacity
  int getCurrentItems() const; 	// returns the current items
  int getCurrentSpells() const; // returns the current spells
  MarketMenu& getMenu();	     // returns the market menu
  Item* getItemByName(const string& name);
  Spell* getSpellByName(const string& name);

  void printInfo() const;  // Prints every item and spell in the market
  void addItem(Item* item); // adds an item in the market
  void addSpell(Spell* spell); // adds a spell in the market
  void removeItem(Item* item); // removes an item from the market
  void removeSpell(Spell* spell); // removes a spell from the market
private:
  int maxCapacity;
  list<Item*> items;
  list<Spell*> spells;
  MarketMenu menu;
};

#endif
