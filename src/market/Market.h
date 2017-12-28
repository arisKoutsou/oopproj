// Market.h --- 
// 
// Filename: Market.h
// Author: George Liontos
// Created: Wed Dec 27 16:29:34 2017 (+0200)

#if !defined(__MARKET_HEADER__)
#define __MARKET_HEADER__

#include <iostream>
#include <list>
#include "../items/Item.h"
#include "../spells/Spell.h"

using namespace std;

class Market {
public:
  Market(int maxCapacity);
  ~Market();

  int getMaxCapacity() const;	// returns the max capacity of the market
  int getCurrentCapacity() const; // returns the current capacity
  int getCurrentItems() const; 	// returns the current items
  int getCurrentSpells() const; // returns the current spells
  list<Item> getItemList() const; // returns the item list
  list<Spell> getSpellList() const; // returns the spell list

  void printInfo() const;  // Prints every item and spell in the market
  void addItem(const Item& item); // adds an item in the market
  void addSpell(const Spell& spell); // adds a spell in the market
  void removeItem(const Item& item); // removes an item from the market
  void removeSpell(const Spell& spell); // removes a spell from the market
private:
  int maxCapacity;
  list<Item> items;
  list<Spell> spells;
};

#endif
