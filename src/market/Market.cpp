// Market.cpp --- 
// 
// Filename: Market.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:42:57 2017 (+0200)

#include <iostream>
#include <list>
#include "Market.h"

using namespace std;

Market :: Market(int _capacity, int _maxItems, int _maxSpells)

  : capacity(_capacity), maxItems(_maxItems), maxSpells(_maxSpells)  {

  if ((maxItems + maxSpells) > capacity) {
    cerr << "The sum of max items and max spells is greater than "
	 << "the capacity of the market (Cannot construct object)"
	 << endl;
    ~Market();
  }
  
  cout << "Creating an instance of Market" << endl;
}

Market :: ~Market() {
  cout << "Destroying a Market" << endl;
}

int Market :: getCapacity() const {
  return capacity;
}

int Market :: getCurrentCapacity() const {
  return (items.size() + spells.size());
}

int Market :: getMaxItems() const {
  return maxItems;
}

int Market :: getCurrentItems() const {
  return (items.size());
}

int Market :: getMaxSpells() const {
  return maxSpells;
}

int Market :: getCurrentSpells() const {
  return (spells.size());
}

list<Item> Market :: getItemList() const {
  return items;
}

list<Spell> Market :: getSpellList() const {
  return spells;
}

