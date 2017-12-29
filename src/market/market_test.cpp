// test.cpp --- 
// 
// Filename: test.cpp
// Author: George Liontos
// Created: Thu Dec 28 15:47:59 2017 (+0200)

#include <iostream>
#include "Market.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Potion.h"
#include "../spells/FireSpell.h"
#include "../spells/IceSpell.h"
#include "../spells/LightningSpell.h"

using namespace std;

int main() {
  // Creating a Market
  Market market(10);

  // Testing Market methods
  cout << "Market's max capacity is: "
       << market.getMaxCapacity() << endl;

  cout << "Current Items in the Market: "
       << market.getCurrentItems() << endl;

  Weapon sword("Excalibur");
  Armor shield("Crimson Parma");
  Potion healthPotion("Elixir of life");
  
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

  IceSpell ice("Frozen Prison");
  FireSpell fire("Living Hell");
  LightningSpell light("Thunderstorm");

  market.addSpell(ice);
  market.addSpell(fire);
  market.addSpell(light);

  market.printInfo();
  
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

  // Gia na doume an mporei na kanei print olo to market.
  cout << endl << "ADDED BY ARIS..." << endl << endl;

  market.print();

  return 0;
}
