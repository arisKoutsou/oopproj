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
#include "../menu/InventoryMenu.h"

using namespace std;

class Inventory {
public:
  Inventory(int maxCapacity);
  ~Inventory();

  int getMaxCapacity() const;	// returns the inventory max capacity
  int getCurrentCapacity() const; // return  the current capacity
  int getCurrentItems() const;	// returns the current items
  int getCurrentSpells() const;	// return the current spells
  list<Item> getItemList() const; // returns the list of items
  list<Spell> getSpellList() const; // return the list of spells

  // Prints all the items and spells, including their info.
  void printInfo() const;
  void addItem(const Item& item); // Adds an item to the inventory
  void addSpell(const Spell& spell); // Adds a spell to the inventory
  void removeItem(const Item& item); // Removes an items from the inventory
  void removeSpell(const Spell& spell); // Removes a spell from the inventory
private:
  int maxCapacity;
  list<Item> items;
  list<Spell> spells;
  InventoryMenu menu;
};

#endif
