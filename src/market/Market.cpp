// Market.cpp --- 
// 
// Filename: Market.cpp
// Author: George Liontos
// Created: Wed Dec 27 16:42:57 2017 (+0200)

#include <iostream>
#include <iomanip>
#include <list>

#include "Market.h"
#include "../game_utils.h"
#include "../items/Item.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Potion.h"
#include "../spells/Spell.h"

using namespace std;

Market :: Market(int _maxCapacity)

  : menu(), maxCapacity(_maxCapacity) {}

Market :: ~Market() {
  while(items.empty() == false) {
    delete items.front();
    items.pop_front();
  }

  while(spells.empty() == false) {
    delete spells.front();
    spells.pop_front();
  }  
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

MarketMenu& Market :: getMenu() {
  return menu;
}

void Market :: printWeapons(vector<Weapon*>& weapons) {
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

void Market :: printArmors(vector<Armor*>& armors) {
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

void Market :: printPotions(vector<Potion*>& potions) {
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

void Market :: printItems() {
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

void Market :: printSpells() {
}

void Market :: printInfo() {
  printItems();
  //  printSpells();
  if (this->getCurrentSpells() != 0) {
    list<Spell*> :: const_iterator spellIterator = spells.begin();
    cout << "Spells:" << endl << endl;
    for ( ; spellIterator != spells.end() ; ++spellIterator) {
      cout << (*spellIterator)->getInfo() << endl;
    }
  } else {
    cout << "No Spells in this Market..." << endl;
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

Item* Market :: getItemByName(const string& name) {
  list<Item*> :: iterator itemIterator = items.begin();

  for ( ; itemIterator != items.end(); ++itemIterator) {
    if ((*itemIterator)->getName() == name) {
      return (*itemIterator);
    }
  }

  return NULL;
}

Spell* Market :: getSpellByName(const string& name) {
  list<Spell*> :: iterator spellIterator = spells.begin();

  for ( ; spellIterator != spells.end(); ++spellIterator) {
    if ((*spellIterator)->getName() == name) {
      return (*spellIterator);
    }
  }

  return NULL;
}
