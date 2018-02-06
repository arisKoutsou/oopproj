#include <iostream>
#include <cstdlib>
#include "../inventory/Inventory.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Potion.h"
#include "../spells/FireSpell.h"
#include "../spells/IceSpell.h"
#include "../spells/LightningSpell.h"

int main() {
  // Creating an inventory
  Inventory inventory(20);

  // Testing inventory methods
  cout << "Inventory's max capacity: "
       << inventory.getMaxCapacity()
       << endl;

  cout << "Items in the inventory: "
       << inventory.getCurrentItems()
       << endl;

  cout << "Spells in the inventory: "
       << inventory.getCurrentSpells()
       << endl;

  // Adding some items and spells in the inventory
  Weapon* sword = new Weapon("Excalibur");
  Armor* shield = new Armor("Crimson Parma");
  Potion* healthPotion = new Potion("Elixir of Life");

  FireSpell* fire = new FireSpell("Unstable Lava");
  IceSpell* ice = new IceSpell("Frozen Hell");
  LightningSpell* light = new LightningSpell("Thunder");
  
  inventory.addItem(sword);
  inventory.addItem(shield);
  inventory.addItem(healthPotion);

  inventory.addSpell(fire);
  inventory.addSpell(ice);
  inventory.addSpell(light);

  cout << "Items in the inventory: "
       << inventory.getCurrentItems()
       << endl;

  cout << "Spells in the inventory: "
       << inventory.getCurrentSpells()
       << endl;

  inventory.printInfo();

  inventory.removeItem(healthPotion);
  inventory.removeItem(shield);

  inventory.removeSpell(light);

  cout << "Items in the inventory: "
       << inventory.getCurrentItems()
       << endl;

  cout << "Spells in the inventory: "
       << inventory.getCurrentSpells()
       << endl;
  
  return EXIT_SUCCESS;
}
