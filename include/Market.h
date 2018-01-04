// Market.h --- 
// 
// Filename: Market.h
// Author: George Liontos
// Created: Wed Dec 27 16:29:34 2017 (+0200)

#if !defined(__MARKET_HEADER__)
#define __MARKET_HEADER__

#include <iostream>
#include <list>
#include "Menu.h"

class Item;
class Spell;

using namespace std;

class Market {
public:
  Market(int maxCapacity);
  ~Market();

  int getMaxCapacity() const;	// returns the max capacity of the market
  int getCurrentCapacity() const; // returns the current capacity
  int getCurrentItems() const; 	// returns the current items
  int getCurrentSpells() const; // returns the current spells
  list<Item*> getItemList() const; // returns the item list
  list<Spell*> getSpellList() const; // returns the spell list
  Menu getMenu() const;	     // returns the market menu
  
  void printInfo() const;  // Prints every item and spell in the market
  void addItem(Item* item); // adds an item in the market
  void addSpell(Spell* spell); // adds a spell in the market
  void removeItem(Item* item); // removes an item from the market
  void removeSpell(Spell* spell); // removes a spell from the market
private:
  int maxCapacity;
  list<Item*> items;
  list<Spell*> spells;
  Menu menu;
};

#endif
