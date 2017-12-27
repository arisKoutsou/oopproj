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
  Market(int capacity, int maxItems, int maxSpells);
  ~Market();

  int getCapacity() const;	// returns the capacity of the market
  int getCurrentCapacity() const; // returns the current capacity
  int getMaxItems() const;	// returns the max items of the market
  int getCurrentItems() const; 	// returns the current items
  int getMaxSpells() const;	// returns the max spells of the market
  int getCurrentSpells() const; // returns the current spells
  list<Item> getItemList() const; // returns the item list
  list<Spell> getSpellList() const; // returns the spell list
private:
  int capacity;
  int maxItems;
  int maxSpells;
  list<Item> items;
  list<Spell> spells;
};

#endif
