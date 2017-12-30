// test.cpp --- 
// 
// Filename: test.cpp
// Author: George Liontos
// Created: Thu Dec 28 15:47:59 2017 (+0200)

#include <iostream>
#include <cstdlib>
#include "../src/market/Market.h"
#include "../src/items/Weapon.h"
#include "../src/items/Armor.h"
#include "../src/items/Potion.h"
#include "../src/spells/FireSpell.h"
#include "../src/spells/IceSpell.h"
#include "../src/spells/LightningSpell.h"

using namespace std;

int main() {
  // Creating a Market
  Market market(20);	// Changed to 20 to test github...

  // Testing Market methods
  cout << "Market's max capacity is: "
       << market.getMaxCapacity() << endl;

  cout << "Current Items in the Market: "
       << market.getCurrentItems() << endl;

  Weapon* sword = new Weapon("Excalibur");
  Armor* shield = new Armor("Crimson Parma");
  Potion* healthPotion = new Potion("Elixir of life");
  
  market.addItem(sword);
  market.addItem(shield);
  market.addItem(healthPotion);

  market.printInfo();
  
  cout << endl;
  cout << "Market's max capacity is: "
       << market.getMaxCapacity() << endl;

  cout << "Current Items in the Market: "
       << market.getCurrentItems() << endl;

  market.removeItem(sword);

  cout << endl;
  cout << "Market's max capacity is: "
       << market.getMaxCapacity() << endl;

  cout << "Current Items in the Market: "
       << market.getCurrentItems() << endl;

  IceSpell* ice = new IceSpell("Frozen Prison");
  FireSpell* fire = new FireSpell("Living Hell");
  LightningSpell* light = new LightningSpell("Thunderstorm");

  market.addSpell(ice);
  market.addSpell(fire);
  market.addSpell(light);

  market.printInfo();	// comments
  
  cout << endl;
  cout << "Market's max capacity is: "
       << market.getMaxCapacity() << endl;

  cout << "Current Spells in the Market: "
       << market.getCurrentSpells() << endl;

  cout << "Current Capacity: "
       << market.getCurrentCapacity() << endl;

  market.removeSpell(fire);

  cout << endl;
  cout << "Market's max capacity is: "
       << market.getMaxCapacity() << endl;

  cout << "Current Items in the Market: "
       << market.getCurrentItems() << endl;

  cout << "Current Spells in the Market: "
       << market.getCurrentSpells() << endl;

  cout << "Current Capacity: "
       << market.getCurrentCapacity() << endl;

  // ADDED A COMMENT JUST NOW
  market.printInfo();

  return 0;
}
