// Inventory.cpp --- 
// 
// Filename: Inventory.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:55:07 2017 (+0200)

#include <iostream>
#include <list>
#include <sstream>
#include "Inventory.h"

using namespace std;

Inventory :: Inventory(int _capacity, int _maxItems, int _maxSpells)

  : capacity(_capacity), maxItems(_maxItems), maxSpells(_maxSpells) {


  if ((maxItems + maxSpells) > capacity) {
    cerr << "The sum of max items and max spells is greater than "
	 << "the capacity of the inventory (Cannot construct object)"
	 << endl;
    ~Inventory();
  }
  
  cout << "Creating an instance of Inventory" << endl;
}

Inventory :: ~Inventory() {
  cout << "Destroying an Inventory" << endl;
}


int Inventory :: getCapacity() const {
  return capacity;
}

int Inventory :: getCurrentCapacity() const {
  return (items.size() + spells.size());
}

int Inventory :: getMaxItems() const {
  return maxItems;
}

int Inventory :: getCurrentItems() const {
  return (items.size());
}

int Inventory :: getMaxSpells() const {
  return maxSpells;
}

int Inventory :: getCurrentSpells() const {
  return (spells.size());
}

list<Item> Inventory :: getItemList() const {
  return items;
}

list<Spell> Inventory :: getSpellList() const {
  return spells;
}

void Inventory :: printInfo() const {
  list<Item> :: iterator itemIterator = items.begin();
  list<Spell> :: iterator spellIterator = spells.begin();

  cout << "Items:" << endl;
  for ( ; itemIterator != items.end(); ++itemIterator) {
    cout << itemIterator.getInfo() << endl;
  }
  cout << endl;

  cout << "Spells:" << endl;
  for ( ; spellIterator != spells.end() ; ++spellIterator) {
    cout << spellIterator.getInfo() << endl;
  }
  cout << endl;
}
