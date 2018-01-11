// Inventory.cpp --- 
// 
// Filename: Inventory.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:55:07 2017 (+0200)

#include <iostream>
#include <list>
#include "Inventory.h"
#include "../items/Item.h"
#include "../spells/Spell.h"
#include "../livings/Hero.h"

using namespace std;

Inventory :: Inventory(int _maxCapacity)

  : menu(*this), maxCapacity(_maxCapacity) {

  cout << "Creating an instance of Inventory" << endl;
}

Inventory :: ~Inventory() {
  while(items.empty() == false) {
    delete items.front();
    items.pop_front();
  }

  while (spells.empty() == false) {
    delete spells.front();
    spells.pop_front();
  }
  
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

// list<Item*> Inventory :: getItemList() const {
//   return items;
// }

// list<Spell*> Inventory :: getSpellList() const {
//   return spells;
// }

void Inventory :: printInfo() const {
  list<Item*> :: const_iterator itemIterator = items.begin();
  list<Spell*> :: const_iterator spellIterator = spells.begin();

  if (items.empty()) {
	  cout << "No items..." << endl;
  } else {
	cout << "Items:" << endl << endl;
	for ( ; itemIterator != items.end(); ++itemIterator) {
		cout << (*itemIterator)->getInfo() << endl;
	}
  }

  if (spells.empty()) {
	  cout << "No spells..." << endl;
  } else {
	  cout << "Spells:" << endl << endl;
	  for ( ; spellIterator != spells.end() ; ++spellIterator) {
		cout << (*spellIterator)->getInfo() << endl;
	  }
  }

}

void Inventory :: addItem(Item* item) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Your inventory is full" << endl;
    return;
  }

  items.push_back(item);
}

void Inventory :: addSpell(Spell* spell) {
  if (this->getCurrentCapacity() == maxCapacity) {
    cout << "Your inventory is full" << endl;
    return;
  }

  spells.push_back(spell);
}

void Inventory :: removeAndDeleteItem(Item* item) {
  // This check can be ommited. If the inventory is already empty
  // then we should not be able to select an item to remove
  if (this->getCurrentCapacity() == 0) {
    cout << "Your inventory is already empty" << endl;
    return;
  }

  items.remove(item);
  delete item;
}

void Inventory :: removeAndDeleteSpell(Spell* spell) {
  // This check can be ommited. If the inventory is already empty
  // then we should not be able to select a spell to remove
  if (this->getCurrentCapacity() == 0) {
    cout << "Your inventory is aldready empty" << endl;
    return;
  }

  spells.remove(spell);
  delete spell;
}

void Inventory :: removeItem(Item* item) {
  if (this->getCurrentCapacity() == 0) {
    cout << "Your inventory is already empty" << endl;
    return;
  }

  items.remove(item);
}

void Inventory :: removeSpell(Spell* spell) {
  if (this->getCurrentCapacity() == 0) {
    cout << "Your inventory is already empty" << endl;
    return;
  }

  spells.remove(spell);
}

Menu Inventory :: getMenu() const {
  return menu;
}

// Added by aris.
Item* Inventory::getItemByName(const string& itemName) const {
	list<Item*>::const_iterator it = items.begin();

	for ( ; it != items.end() ; it++) {
		if ((*it)->getName() == itemName) {
			return *it;
		}
	}

	return NULL;
}

Spell* Inventory::getSpellByName(const string& spellName) const {
	list<Spell*>::const_iterator it = spells.begin();

	for ( ; it != spells.end() ; it++) {
		if ((*it)->getName() == spellName) {
			return *it;
		}
	}

	return NULL;
}
