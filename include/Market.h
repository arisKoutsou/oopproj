// Market.h --- 
// 
// Filename: Market.h
// Author: George Liontos
// Created: Wed Dec 27 16:29:34 2017 (+0200)

#if !defined(__MARKET_HEADER__)
#define __MARKET_HEADER__

#include <iostream>
#include <vector>
#include <list>

#include "AllMenus.h"

class Item;
class Spell;
class Weapon;
class Armor;
class Potion;
class IceSpell;
class FireSpell;
class LightningSpell;

using namespace std;

class Market {
public:
  explicit Market(int maxCapacity = 20);
  ~Market();

  int getMaxCapacity() const;	// returns the max capacity of the market
  int getCurrentCapacity() const; // returns the current capacity
  int getCurrentItems() const; 	// returns the current items
  int getCurrentSpells() const; // returns the current spells
  MarketMenu& getMenu();	     // returns the market menu
  Item* getItemByName(const string& name);
  Spell* getSpellByName(const string& name);

  void printInfo();  // Prints every item and spell in the market
  void addItem(Item* item); // adds an item in the market
  void addSpell(Spell* spell); // adds a spell in the market
private:
  void printItems();
  void printWeapons(vector<Weapon*>& weapons);
  void printArmors(vector<Armor*>& armors);
  void printPotions(vector<Potion*>& potions);
  void printSpells();
  void printIceSpells(vector<IceSpell*>& iceSpells);
  void printFireSpells(vector<FireSpell*>& fireSpells);
  void printLightningSpells(vector<LightningSpell*>& lightningSpells);
  int maxCapacity;
  list<Item*> items;
  list<Spell*> spells;
  MarketMenu menu;
};

#endif
