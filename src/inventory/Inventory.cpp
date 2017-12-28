// Inventory.cpp --- 
// 
// Filename: Inventory.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:55:07 2017 (+0200)

#include <iostream>
#include <list>
#include "Inventory.h"

using namespace std;

Inventory :: Inventory(int _maxCapacity)

  : maxCapacity(_maxCapacity) {

  cout << "Creating an instance of Inventory" << endl;
}

Inventory :: ~Inventory() {
  cout << "Destroying an Inventory" << endl;
}

int Inventory :: getMaxCapacity() const {
  return maxCapacity;
}

int Inventory :: getCurrentCapacity() const {
  return (items.size() + spells.size());
}

int Inventory :: getCurrentItems() const {
  return (items.size());
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
  list<Item> :: const_iterator itemIterator = items.begin();
  list<Spell> :: const_iterator spellIterator = spells.begin();

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

void Inventory :: addItem(const Item& item) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Your inventory is full" << endl;
    return;
  }

  items.push_back(item);
}

void Inventory :: addSpell(const Spell& spell) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Your inventory is full" << endl;
    return;
  }

  spells.push_back(spell);
}

void Inventory :: removeItem(const Item& item) {
  // This check can be ommited. If the inventory is already empty
  // then we should not be able to select an item to remove
  if (this->getCurrentCapacity() == 0) {
    cout << "Your inventory is already empty" << endl;
    return;
  }

  items.remove(item);
}

void Inventory :: removeSpell(const Spell& spell) {
  // This check can be ommited. If the inventory is already empty
  // then we should not be able to select a spell to remove
  if (this->getCurrentCapacity() == 0) {
    cout << "Your inventory is aldready empty" << endl;
    return;
  }

  spells.remove(spell);
}
