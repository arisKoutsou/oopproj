// Inventory.h --- 
// 
// Filename: Inventory.h
// Author: George Liontos
// Created: Wed Dec 27 16:54:52 2017 (+0200)

#if !defined(__INVENTORY_HEADER__)
#define __INVENTORY_HEADER__

#include <iostream>
#include "../items/Item.h"
#include "../spells/Spell.h"

using namespace std;

class Inventory {
public:
  Inventory(int capacity, int maxItems, int maxSpells);
  ~Inventory();

  int getCapacity() const;	// returns the inventory capacity
  int getCurrentCapacity() const; // return  the current capacity
  int getMaxItems() const;	// returns the maximum items
  int getMaxSpells() const;	// returns the maximum spells
  int getCurrentItems() const;	// returns the current items
  int getCurrentSpells() const;	// return the current spells
  list<Item> getItemList() const; // returns the list of items
  list<Spell> getSpellList() const; // return the list of spells

  // Prints all the items and spells, including their info.
  void printInfo() const; 	
private:
  int capacity;
  int maxItems;
  int maxSpells;
  list<Item> items;
  list<Spell> spells;
};

#endif
