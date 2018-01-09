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
#include "../spells/Spell.h"

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
  shield(NULL)
{

}

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
bool Hero :: operator==(const Hero& rValue) const {
  bool sameLiving;
  bool sameMagicPower;
  bool sameStrength;
  bool sameAgility;
  bool sameDexterity;
  bool sameMoney;
  bool sameExperience;
  // There's no need to check if they've got the same inventory

  sameLiving = (static_cast<Living>(*this) == rValue);
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

void Hero :: moveUp() throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroY == this->grid->getMaxY()) {
    throw HeroMoveException("You can't move up any further");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setY(heroY + 1);
  }
}

void Hero :: moveDown(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();
 
  if (heroY == 0) {
    throw HeroMoveException("You can't move down any further");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setY(heroY - 1);
  }
}

void Hero :: moveLeft(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroX == 0) {
    throw HeroMoveException("You can't move left any further");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setX(heroX - 1);
  }
}

void Hero :: moveRight(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroX == grid.getMaxX()) {
    throw HeroMoveException("You can't move right any further");
  } else {
    this->grid->removeLiving(heroY, heroX, this);
    this->getPosition().setX(heroX + 1);
  }
}

void Hero :: move(directions direction) throw() {
  switch (direction) {
  case UP: moveUp(); return;
  case DOWN: moveDown(); return;
  case LEFT: moveLeft(); return;
  case RIGHT: moveRight(); return;
  default: throw HeroMoveException("Unknown direction"); return;
  }
}

string Hero :: getUserInput() {
  cout << "Please enter the name of the item/spell you want to equip" << endl;

  string input;
  cin >> input;

  return input;
}

void Hero :: equip(const string& name) {
  Item* itemToEquip = inventory.getItemByName(name);

  if (itemToEquip != NULL) {
    string kind = itemToEquip->kindOf();
    this->inventory.removeItem(itemToEquip);
    return;
  }

  Spell* spellToEquip = inventory.getSpellByName(name);

  if (spellToEquip != NULL) {
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

  while ((selection = this->inventory.getMenu().getSelection())) {
    switch (selection) {
    case 1: {
      this->inventory.printInfo();
      break;
    }

    case 2: {
      string input = getUserInput();
    
      this->equip(input);
      break;
    }

    case 3: {
      string input = getUserInput();

      this->discard(input);
      break;      
    }

    case 4: {
      string input = getUserInput();

      this->usePotion(input);
      break;
    }
      
    case 5: {
      this->inventory.getMenu().clearMenu();
      return;
    }
    } 
  }
}

void Hero::buy(const string& itemName) {
	Item* itemToBuy = inventory.getItemByName(itemName);
	if (itemToBuy != NULL) {
		inventory.addItem(itemToBuy);
		money -= itemToBuy->buyFor();
		return;
	}

	Spell* spellToBuy = inventory.getSpellByName(itemName);
	if (spellToBuy != NULL) {
		inventory.addSpell(spellToBuy);
		money -= spellToBuy->getValue();
		return;
	}
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
}
