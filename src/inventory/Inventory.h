// Inventory.h --- 
// 
// Filename: Inventory.h
// Author: George Liontos
// Created: Wed Dec 27 16:54:52 2017 (+0200)

#if !defined(__INVENTORY_HEADER__)
#define __INVENTORY_HEADER__

#include <iostream>
#include <list>
#include "../menu/Menu.h"

class Item;
class Spell;

using namespace std;

class Inventory {
public:
  explicit Inventory(int maxCapacity = 20);
  ~Inventory();

  int getMaxCapacity() const;	// returns the inventory max capacity
  int getCurrentCapacity() const; // return  the current capacity
  int getCurrentItems() const;	// returns the current items
  int getCurrentSpells() const;	// return the current spells
  //  list<Item*> getItemList() const; // returns the list of items
  //  list<Spell*> getSpellList() const; // return the list of spells
  Menu getMenu() const; // returns the menu
  Item* getItemByName(const string& name) const; // returns a pointer to an item.
  Spell* getSpellByName(const string& spellName) const;// return pointer to spell.
  
  // Prints all the items and spells, including their info.
  void printInfo() const;
  void addItem(Item* item); // Adds an item to the inventory
  void addSpell(Spell* spell); // Adds a spell to the inventory
  void removeAndDeleteItem(Item* item); // Completely removes an items from the inventory
  void removeAndDeleteSpell(Spell* spell); // Completely removes a spell from the inventory
  void removeItem(Item* item); // Removes an item from the inventory
  void removeSpell(Spell* spell); // Removes a spell from the inventory
private:
  int maxCapacity;
  list<Item*> items;
  list<Spell*> spells;
  Menu menu;
};

#endif
