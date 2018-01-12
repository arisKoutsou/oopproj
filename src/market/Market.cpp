// Market.cpp --- 
// 
// Filename: Market.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:42:57 2017 (+0200)

#include <iostream>
#include <list>
#include "./Market.h"
#include "../items/Item.h"
#include "../spells/Spell.h"

using namespace std;

Market :: Market(int _maxCapacity)

  : menu(*this), maxCapacity(_maxCapacity) {

  cout << "Creating an instance of Market" << endl;
}

Market :: ~Market() {
  while(items.empty() == false) {
    delete items.front();
    items.pop_front();
  }

  while(spells.empty() == false) {
    delete spells.front();
    spells.pop_front();
  }
  
  cout << "Destroying a Market" << endl;
}

int Market :: getMaxCapacity() const {
  return maxCapacity;
}

int Market :: getCurrentCapacity() const {
  return (items.size() + spells.size());
}

int Market :: getCurrentItems() const {
  return (items.size());
}

int Market :: getCurrentSpells() const {
  return (spells.size());
}

Menu& Market :: getMenu() {
  return menu;
}

void Market :: printInfo() const {
  list<Item*> :: const_iterator itemIterator = items.begin();
  list<Spell*> :: const_iterator spellIterator = spells.begin();

  cout << "Items:" << endl << endl;
  for ( ; itemIterator != items.end(); ++itemIterator) {
    cout << (*itemIterator)->getInfo() << endl;
  }

  cout << "Spells:" << endl << endl;
  for ( ; spellIterator != spells.end() ; ++spellIterator) {
    cout << (*spellIterator)->getInfo() << endl;
  }
}

void Market :: addItem(Item* item) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Market is full" << endl;
    return;
  }
  
  items.push_back(item);
}

void Market :: addSpell(Spell* spell) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Market is full" << endl;
    return;
  }

  spells.push_back(spell);
}

void Market :: removeItem(Item* item) {
  if (this->getCurrentCapacity() == 0) {
    cout << "Market is already empty" << endl;
    return;
  }

  items.remove(item);
  delete item;
}

void Market :: removeSpell(Spell* spell) {
  if (this->getCurrentCapacity() == 0) {
    cout << "Market is already empty" << endl;
    return;
  }

  spells.remove(spell);
  delete spell;
}
