// Market.cpp --- 
// 
// Filename: Market.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:42:57 2017 (+0200)

#include <iostream>
#include <list>
#include "Market.h"

using namespace std;

Market :: Market(int _maxCapacity)

  : maxCapacity(_maxCapacity) {

  cout << "Creating an instance of Market" << endl;
}

Market :: ~Market() {
  cout << "Destroying a Market" << endl;
}

int Market :: getMaxCapacity() const {
  return maxCapacity;
}

int Market :: getCurrentCapacity() const {
  return (items.size() + spells.size());x
}

int Market :: getCurrentItems() const {
  return (items.size());
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

void Market :: printInfo() const {
  list<Item> :: const_iterator itemIterator = items.begin();
  list<Spell> :: const_iterator spellIterator = spells.begin();

  cout << "Items:" << endl;
  for ( ; itemIterator != items.end(); ++itemIterator) {
    cout << (*itemIterator).getInfo() << endl;
  }
  cout << endl;

  cout << "Spells:" << endl;
  for ( ; spellIterator != spells.end() ; ++spellIterator) {
    cout << spellIterator.getInfo() << endl;
  }
  cout << endl;
}

void Market :: addItem(const Item& item) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Market is full" << endl;
    return;
  }
  
  items.push_back(item);
}

void Market :: addSpell(const Spell& spell) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Market is full" << endl;
    return;
  }

  spells.push_back(spell);
}

void Market :: removeItem(const Item& item) {
  if (this->getCurrentCapacity() == 0) {
    cout << "Market is already empty" << endl;
    return;
  }
  
  items.remove(item);
}

void Market :: removeSpell(const Spell& spell) {
  if (this->getCurrentCapacity() == 0) {
    cout << "Market is already empty" << endl;
    return;
  }

  spells.remove(item);
}