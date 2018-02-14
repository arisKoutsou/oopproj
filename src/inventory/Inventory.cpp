// Inventory.cpp --- 
// 
// Filename: Inventory.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:55:07 2017 (+0200)

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include "Inventory.h"

#include "../game_utils.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Potion.h"
#include "../items/Item.h"
#include "../spells/Spell.h"
#include "../livings/Hero.h"

using namespace std;

Inventory :: Inventory(int _maxCapacity)

  : menu(), maxCapacity(_maxCapacity) {}

Inventory :: ~Inventory() {
  while(items.empty() == false) {
    delete items.front();
    items.pop_front();
  }

  while (spells.empty() == false) {
    delete spells.front();
    spells.pop_front();
  }
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

bool Inventory :: hasItems() const {
  return (items.empty() == false);
}

bool Inventory :: hasSpells() const {
  return (spells.empty() == false);
}

bool Inventory::hasPotions() const {
	list<Item*> :: const_iterator itemIterator = items.begin();

	for ( ; itemIterator != items.end() ; itemIterator++) {
		if ((*itemIterator)->kindOf() == "Potion") {
			return true;
		}
	}

	return false;
}

void Inventory :: printWeapons(vector<Weapon*>& weapons) {
  if (weapons.size() == 0) return;
  cout << '+' << string(66, '-') << '+' << endl;
  cout << '|' << setw(33 + 7/2) << "WEAPONS"
       << setw(34 - 7/2) << '|' << endl;
  printWeaponFrame();
  cout << '|'
       << setw(14) << "NAME" << setw(11) << '|'
       << setw(6) << "PRICE" << setw(2) << '|'
       << setw(10) << "MIN LEVEL" << setw(2) << '|'
       << setw(7) << "DAMAGE" << setw(2) << '|'
       << setw(11) << "TWO HANDED" << setw(2) << '|'
       << endl;
  for (size_t i = 0U; i != weapons.size(); ++i) {
    weapons[i]->getInfo();
  }
  printWeaponFrame();
  cout << endl << endl;
}

void Inventory :: printArmors(vector<Armor*>& armors) {
  if (armors.size() == 0) return;
  cout << '+' << string(63, '-') << '+' << endl;
  cout << '|' << setw(34) << "ARMORS" << setw(30) << '|' << endl;
  printArmorFrame();
  cout << '|'
       << setw(14) << "NAME" << setw(11) << '|'
       << setw(6) << "PRICE" << setw(2) << '|'
       << setw(10) << "MIN LEVEL" << setw(2) << '|'
       << setw(17) << "DAMAGE REDUCTION" << setw(2) << '|'
       << endl;
  for (size_t i = 0U; i != armors.size(); ++i) {
    armors[i]->getInfo();
  }
  printArmorFrame();
  cout << endl << endl;
}

void Inventory :: printPotions(vector<Potion*>& potions) {
  if (potions.size() == 0) return;
  cout << '+' << string(106, '-') << '+' << endl;
  cout << '|' << setw(53 + 7/2) << "POTIONS" << setw(54 - 7/2) << '|' << endl;
  printPotionFrame();
  cout << '|'
       << setw(14) << "NAME" << setw(11) << '|'
       << setw(6) << "PRICE" << setw(2) << '|'
       << setw(10) << "MIN LEVEL" << setw(2) << '|'
       << setw(15) << "STRENGTH BONUS" << setw(2) << '|'
       << setw(16) << "DEXTERITY BONUS" << setw(2) << '|'
       << setw(14) << "AGILITY BONUS" << setw(2) << '|'
       << setw(9) << "DURATION" << setw(2) << '|'
       << endl;
  for (size_t i = 0U; i != potions.size(); ++i) {
    potions[i]->getInfo();
  }
  printPotionFrame();
  cout << endl << endl;
}

void Inventory :: printItems() {
  if (this->getCurrentItems() == 0) {
    cout << endl << "No items in this market" << endl << endl;
    return;
  } else {
    list<Item*> :: const_iterator it = items.begin();
    vector<Weapon*> weapons;
    vector<Armor*> armors;
    vector<Potion*> potions;
    for ( ; it != items.end(); ++it) {
      string kind = (*it)->kindOf();
      if (kind == "Weapon") {
	weapons.push_back(static_cast<Weapon*>(*it));
      } else if (kind == "Armor") {
	armors.push_back(static_cast<Armor*>(*it));
      } else if (kind == "Potion") {
	potions.push_back(static_cast<Potion*>(*it));
      }
    }
    printWeapons(weapons);
    printArmors(armors);
    printPotions(potions);
  }
}

void Inventory :: printSpells() {

}

void Inventory :: printInfo() const {
  list<Item*> :: const_iterator itemIterator = items.begin();
  list<Spell*> :: const_iterator spellIterator = spells.begin();

  if (items.empty()) {
    cout << "No items..." << endl;
  } else {
    cout << "Items:" << endl << endl;
    for ( ; itemIterator != items.end(); ++itemIterator) {
      (*itemIterator)->getInfo();
      cout << endl;
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

InventoryMenu& Inventory :: getMenu() {
  return menu;
}

void Inventory :: printSpells() const {
  list<Spell*> :: const_iterator it = spells.begin();
  for ( ; it != spells.end(); ++it) {
    cout << (*it)->getInfo() << endl;
  }
  cout << endl;
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
