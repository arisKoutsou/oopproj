/*
 * Hero.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#include "Hero.h"
#include "../grid/Grid.h"
#include "../exceptions/heroExceptions.h"
#include "../items/Item.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Potion.h"
#include "../spells/Spell.h"
#include "../inventory/Inventory.h"
#include "../market/Market.h"

Hero::Hero(
	Grid* gr,
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d,
	int x,
	int y
)
: Living(gr, nam, hp, x, y),
  magicPower(mp),
  strength(s), agility(a),
  dexterity(d), money(450),
  expirience(0), inventory(),
  leftHandWeapon(NULL),
  rightHandWeapon(NULL),
  shield(NULL) {}

int Hero::getAgility() const {
	return agility;
}

int Hero::getDexterity() const {
	return dexterity;
}

int Hero::getExpirience() const {
	return expirience;
}

int Hero::getMagicPower() const {
	return magicPower;
}

int Hero::getMoney() const {
	return money;
}

int Hero::getStrength() const {
	return strength;
}

// Implemented by: (George Liontos)
Inventory& Hero :: getInventory() {
  return inventory;
}

bool Hero :: operator==(const Hero& rValue) const {
  bool sameLiving;
  bool sameMagicPower;
  bool sameStrength;
  bool sameAgility;
  bool sameDexterity;
  bool sameMoney;
  bool sameExperience;
  // There's no need to check if they've got the same inventory

  sameLiving = Living::operator==(rValue);
  sameMagicPower = (this->magicPower == rValue.magicPower) ? true : false;
  sameStrength = (this->strength == rValue.strength) ? true : false;
  sameAgility = (this->agility == rValue.agility) ? true : false;
  sameDexterity = (this->dexterity == rValue.dexterity) ? true : false;
  sameMoney = (this->money == rValue.money) ? true : false;
  sameExperience = (this->expirience == rValue.expirience) ? true : false;

  return (sameLiving && sameMagicPower &&
	  sameStrength && sameDexterity &&
	  sameAgility && sameMoney &&
	  sameExperience);
}

void Hero :: moveUp() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroY == this->grid->getMaxY()) {
    throw HeroMoveException("You can't move up any further");
  } else if (this->grid->getTile(heroY + 1, heroX).isNonAccessible()) {
    throw HeroMoveException("You can't move in a non accessible tile");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setY(heroY + 1);
    this->grid->addLiving(heroY + 1, heroX, this);
  }
}

void Hero :: moveDown() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();
 
  if (heroY == 0) {
    throw HeroMoveException("You can't move down any further");
  } else if (this->grid->getTile(heroY - 1, heroX).isNonAccessible()) {
    throw HeroMoveException("You can't move in a non accessible tile");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setY(heroY - 1);
    this->grid->addLiving(heroY - 1, heroX, this);
  }
}

void Hero :: moveLeft() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroX == 0) {
    throw HeroMoveException("You can't move left any further");
  } else if (this->grid->getTile(heroY, heroX - 1).isNonAccessible()) {
    throw HeroMoveException("You can't move in a non accessible tile");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setX(heroX - 1);
    this->grid->addLiving(heroY, heroX - 1, this);
  }
}

void Hero :: moveRight() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroX == grid->getMaxX()) {
    throw HeroMoveException("You can't move right any further");    
  } else if (this->grid->getTile(heroY, heroX + 1).isNonAccessible()) {
    throw HeroMoveException("You can't move in a non accessible tile");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setX(heroX + 1);
    this->grid->addLiving(heroY, heroX + 1, this);
  }
}

void Hero :: move(directions direction) {
  try {
    switch (direction) {
    case UP: moveUp(); break;
    case DOWN: moveDown(); break;
    case LEFT: moveLeft(); break;
    case RIGHT: moveRight(); break;
    default: throw HeroMoveException("Unknown direction"); break;
    }
  }
  catch (HeroMoveException& e) {
    cout << e.what() << endl;
  }
}

string Hero :: getUserInput(const string& prompt) {
  cout << prompt << endl;

  string input;
  cin >> input;

  return input;
}

void Hero :: equip(const string& name) {
  Item* itemToEquip = inventory.getItemByName(name);

  if (itemToEquip != NULL) {
    string kind = itemToEquip->kindOf();

    if (kind == "Weapon") {
      Weapon* weaponToEquip = static_cast<Weapon*>(itemToEquip);
      this->equipWeapon(weaponToEquip);
    } else if (kind == "Armor") {
      Armor* armorToEquip = static_cast<Armor*>(itemToEquip);
      this->equipArmor(armorToEquip);

    } else if (kind == "Potion") {
      cout << "You can't equip a potion" << endl;
      return;
    }
    this->inventory.removeItem(itemToEquip);
    return;
  }

  Spell* spellToEquip = inventory.getSpellByName(name);

  if (spellToEquip != NULL) {
    this->equipSpell(spellToEquip);
    this->inventory.removeSpell(spellToEquip);
    return;
  }

  cout << "There's no such item or spell in your inventory" << endl;
}

void Hero :: discard(const string& name) {
  Item* itemToDiscard = inventory.getItemByName(name);

  if (itemToDiscard != NULL) {
    this->inventory.removeAndDeleteItem(itemToDiscard);
    return;
  }

  Spell* spellToDiscard = inventory.getSpellByName(name);

  if (spellToDiscard != NULL) {
    this->inventory.removeAndDeleteSpell(spellToDiscard);
    return;
  }

  cout << "There's no such item or spell in your inventory" << endl;
}

void Hero :: usePotion(const string& name) {
  Item* potionToBeUsed = inventory.getItemByName(name);

  if (potionToBeUsed != NULL) {
    this->inventory.removeAndDeleteItem(potionToBeUsed);
    return;
  }

  cout << "There's no such Potion in your inventory" << endl;
}

void Hero :: checkInventory() {
  this->inventory.getMenu().displayMenu();
  int selection;
  string equipPrompt = "Please enter the name of the item/spell you want to equip";
  string discardPrompt = "Please enter the name of the item/spell you want to discard";
  string usePotionPrompt = "Please enter the name of the potion you want to use";
  
  while ((selection = this->inventory.getMenu().getSelection())) {
    switch (selection) {
    case 1: {
      this->inventory.printInfo();
      break;
    }
    case 2: {
      string input = getUserInput(equipPrompt);
    
      this->equip(input);
      break;
    }
    case 3: {
      string input = getUserInput(discardPrompt);

      this->discard(input);
      break;      
    }
    case 4: {
      string input = getUserInput(usePotionPrompt);

      this->usePotion(input);
      break;
    } 
    case 5: {
      this->inventory.getMenu().clearMenu();
      return;
    }      
    }
    this->inventory.getMenu().displayMenu();
  }
}

void Hero::buy(const string& itemName) {
	// Market* currentMarket;

	// if ( grid->getTile(getPosition().getY(), getPosition().getX()).hasMarket() ) {
	// 	currentMarket =
	// 		grid->getTile(
	// 			getPosition().getY(),
	// 			getPosition().getX()
	// 		).getMarket();
	// } else {
	// 	cout << endl << "There is no market at the current Tile!" << endl;
	// 	return;
	// }
	// Item* itemToBuy;

	// list<Item*> :: const_iterator itemIterator = currentMarket->getItemList().begin();

	// for ( ; itemIterator != currentMarket->getItemList().end() ; ++itemIterator) {
	// 	if ((*itemIterator)->getName() == itemName) {
	// 		if ((*itemIterator)->buyFor() < this->getMoney()) {
	// 			this->inventory.addItem(*itemIterator);
	// 			this->money -= (*itemIterator)->buyFor();
	// 			currentMarket->removeItem(*itemIterator);
	// 			return;
	// 		} else {
	// 			cout << endl << "Not enough gold. You need "
	// 				<< (*itemIterator)->buyFor() - this->getMoney() << " more." << endl;
	// 		}
	// 	} else {
	// 		cout << endl << "Item/Spell doesn't exist on this Market." << endl;
	// 	}

	// }
  Market* currentMarket = grid->getTile(getPosition().getY(), getPosition().getX()).getMarket();

  Item* itemToBuy = currentMarket->getItemByName(itemName);

  if (itemToBuy != NULL) {
    inventory.addItem(itemToBuy);
    money -= itemToBuy->buyFor();
    return;
  }

  Spell* spellToBuy = currentMarket->getSpellByName(itemName);

  if (spellToBuy != NULL) {
    inventory.addSpell(spellToBuy);
    money -= spellToBuy->getValue();
    return;
  }

  cout << "There's no item/spell with this name" << endl;
}

void Hero::sell(const string& itemName) {
        Item* itemToSell = inventory.getItemByName(itemName);
	if (itemToSell != NULL) {
		inventory.removeItem(itemToSell);
		money += itemToSell->sellsFor();
		return;
	}

	Spell* spellToSell = inventory.getSpellByName(itemName);
	if (spellToSell != NULL) {
		inventory.removeSpell(spellToSell);
		money += spellToSell->getValue();
		return;
	}

	cout << "There's no item/spell with this name" << endl;
}

bool Hero :: usesBothHands() const {
  return (leftHandWeapon != NULL && rightHandWeapon != NULL);
}

bool Hero :: usesOneHand() const {
  return (leftHandWeapon != NULL || rightHandWeapon != NULL);
}

bool Hero :: usesLeftHand() const {
  return (leftHandWeapon != NULL);
}

bool Hero :: usesRightHand() const {
  return (rightHandWeapon != NULL);
}

void Hero :: equipWeapon(Weapon* weapon) {
  bool weaponNeedsBothHands = weapon->needsBothHands();
      
  if (weaponNeedsBothHands) {
    if (this->usesLeftHand()) {
      this->inventory.addItem(this->leftHandWeapon);
    }
    if (this->usesRightHand()) {
      this->inventory.addItem(this->rightHandWeapon);
    }
    this->leftHandWeapon = this->rightHandWeapon = weapon;
  } else {
    if (this->usesBothHands()) {
      string hand;
      do {
	cout << "You are using both hands. Would you like to equip"
	     << " the weapon to left of right hand?" << endl;

	cin >> hand;

	if (hand == "left") {
	  this->inventory.addItem(this->leftHandWeapon);
	  this->leftHandWeapon = weapon;
	} else if (hand == "right") {
	  this->inventory.addItem(this->rightHandWeapon);
	  this->rightHandWeapon = weapon;
	}
      } while (hand != "left" || hand != "right");
    } else if (this->usesLeftHand()) {
      this->leftHandWeapon = weapon;
    } else {
      this->rightHandWeapon = weapon;
    }
  }    
}

void Hero :: equipArmor(Armor* armor) {
  if (this->shield != NULL) {
    this->inventory.addItem(shield);
  }
  this->shield = armor;  
}

void Hero :: equipSpell(Spell* spell) {
  if (this->spells.size() != 3) {
    this->spells.push_back(spell);
  }
}

void Hero :: printStats() const {
  Living :: printStats();
  cout << "Mana: " << this->magicPower << endl
       << "Stregth: " << this->strength << endl
       << "Agility: " << this->agility << endl
       << "Dexterity: " << this->dexterity << endl
       << "Money: " << this->money << endl
       << "Experience: " << this->expirience << endl
       << endl
       << "Left Hand: " << ((this->leftHandWeapon) ? this->leftHandWeapon->getInfo() : "") << endl
       << endl
       << "Right Hand: " << ((this->rightHandWeapon) ? this->rightHandWeapon->getInfo() : "")
       << endl;
}

void Hero :: enterMarket(Market* market) {
  market->getMenu().displayMenu();
  int selection;
  string buyPrompt = "Please enter the name of the item/spell you want to buy";
  string sellPrompt = "Please ente the name of the item/spell you want to sell";
  
  while ((selection = market->getMenu().getSelection())) {
    switch (selection) {
    case 1: {
     market->printInfo();
     break; 
    }
    case 2: {
      string input = getUserInput(buyPrompt);
      
      this->buy(input);
      break;
    }
    case 3: {
      cout << "You have these items/spells for sale" << endl << endl;
      this->inventory.printInfo();
      string input = getUserInput(sellPrompt);
      
      this->sell(input);
      break;
    }
    case 4: {
      market->getMenu().clearMenu();
      return;
    }
    }
  }
}
