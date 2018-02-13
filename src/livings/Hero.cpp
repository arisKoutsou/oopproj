/*
 * Hero.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#include <cstring>
#include "Hero.h"

#include <iomanip>

#include "../game_utils.h"
#include "../grid/Grid.h"
#include "../exceptions/heroExceptions.h"
#include "../items/Item.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Potion.h"
#include "../spells/Spell.h"
#include "../spells/IceSpell.h"
#include "../spells/FireSpell.h"
#include "../spells/LightningSpell.h"
#include "../inventory/Inventory.h"
#include "../market/Market.h"
#include "../random/Random.h"
#include "Monster.h"

Hero::Hero(
	Grid* gr,
	string nam,
	int y,
	int x,
	int hp,
	int mp,
	int s,
	double a,
	int d
)
: Living(gr, y, x, nam, hp),
  magicPower(mp),
  strength(s), agility(a),
  dexterity(d), money(450),
  expirience(0), inventory(),
  leftHandWeapon(NULL),
  rightHandWeapon(NULL),
  battleMenu(),
  gameMenu(),
  shield(NULL),
  monstersKilled(0),
  maxMagicPower(mp),
  milestone(200)
{
  grid->addLiving(y, x, this);
}

Hero :: ~Hero() {
  delete leftHandWeapon;
  delete rightHandWeapon;
  delete shield;

  while (spells.empty() == false) {
    delete spells.front();
    spells.pop_front();
  }
}

double Hero::getAgility() const {
	return agility;
}

int Hero::getDexterity() const {
	return dexterity;
}

int Hero::getExperience() const {
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

int Hero :: getMaxMagicPower() const {
  return maxMagicPower;
}
  
double Hero::getDamageReductionFactor() const {
	double result = 0.0;

	if (shield != NULL) {
		result += shield->getDamageReductionFactor();
	}

	return result;
}

BasicMenu& Hero :: getGameMenu() {
  return gameMenu;
}

const Grid::Tile& Hero::getTile() {
	return grid->getTile(
		getPosition().getY(),
		getPosition().getX()
	);
}

void Hero :: setMoney(int money) {
  this->money = money;
}

void Hero :: setExperience(int experience) {
  this->expirience = experience;
}

void Hero :: setMagicPower(int mana) {
  this->magicPower = mana;
}

void Hero :: resetBattleStats() {
  monstersKilled = 0;
}

int Hero :: getMonstersKilled() const {
  return monstersKilled;
}

int Hero :: getExperienceMilestone() const {
	return milestone;
}

void Hero :: nextMilestone() {
	milestone += 100;
}

void Hero :: respawn() {
  this->setHealthPower(maxHealth/2);
}

// Implemented by: (George Liontos)
// Please don't even try and understand what this code does
// That was a hard night computing offsets for right printing
void Hero :: printStats() const {
  printHeroFrame();
  cout << '|'
       << setw(10) << "NAME" << setw(7) << '|'
       << setw(6) << "LEVEL" << setw(2) << '|'
       << setw(5) << "HP" << setw(4) << '|'
       << setw(6) << "MANA" << setw(3) << '|'
       << setw(10) << "STRENGTH" << setw(3) << '|'
       << setw(9) << "AGILITY" << setw(3) << '|'
       << setw(11) << "DEXTERITY" << setw(3) << '|'
       << setw(13) << "LEFT WEAPON" << setw(3) << '|'
       << setw(14) << "RIGHT WEAPON" << setw(3) << '|'
       << endl;
  printHeroFrame();
  size_t nameLength = getName().length();
  int levelDigits = getDigits(level);
  int hpDigits = getDigits(getHealthPower());
  int manaDigits = getDigits(getMagicPower());
  int strengthDigits = getDigits(getStrength());
  int agilityDigits = getDigits(getAgility()) + 2;
  int dexDigits = getDigits(getDexterity());
  string leftWeapon = (leftHandWeapon == NULL) ? "NONE" : leftHandWeapon->getName();
  string rightWeapon = (rightHandWeapon == NULL) ? "NONE" : rightHandWeapon->getName();
  size_t leftWeaponLength = (leftHandWeapon == NULL) ? 4 : leftWeapon.length();
  size_t rightWeaponLength = (rightHandWeapon == NULL) ? 4 : rightWeapon.length();
  cout << '|'
       << setw(9 + nameLength/2) << getName() << setw(8 - nameLength/2) << '|'
       << setw(4 + levelDigits/2) << level << setw(4 - levelDigits/2) << '|'
       << setw(5 + hpDigits/2) << getHealthPower() << setw(4 - hpDigits/2) << '|'
       << setw(4 + manaDigits/2) << getMagicPower() << setw(5 - manaDigits/2) << '|'
       << setw(7 + strengthDigits/2) << getStrength() << setw(6 - strengthDigits/2) << '|'
       << setw(6 + agilityDigits/2) << setprecision(2) << getAgility() << setw(6 - agilityDigits/2) << '|'
       << setw(7 + dexDigits/2) << getDexterity() << setw(9 - dexDigits) << '|'
       << setw(8 + leftWeaponLength/2) << leftWeapon << setw(8 - leftWeaponLength/2) << '|'
       << setw(9 + rightWeaponLength/2) << rightWeapon << setw(8 - rightWeaponLength/2) << '|'
       << endl;
  printHeroFrame();
}

void Hero::updatePotions() {
  // (George): Alternative Implementation

  list<Potion*> :: iterator potionsIterator = potions.begin();  

  for ( ; potionsIterator != potions.end(); ++potionsIterator) {
    (*potionsIterator)->roundPassed();

    if ((*potionsIterator)->getRoundsEffective() == -1) {
      double strengthBoost = (*potionsIterator)->getStrengthBoost();
      double agilityBoost = (*potionsIterator)->getAgilityBoost();
      double dexterityBoost = (*potionsIterator)->getDexterityBoost();
      
      if (strengthBoost != 0.0) {
	this->strength /= strengthBoost + 1.0;
      }

      if (agilityBoost != 0.0) {
	this->agility /= agilityBoost + 1.0;
      }

      if (dexterityBoost != 0.0) {
	this->dexterity = dexterityBoost + 1.0;
      }      

      // Rounding up 1 digit (It's like calling ceil())
      this->strength += (strengthBoost == 0.0) ? 0 : 1;
      this->dexterity += (dexterityBoost == 0.0) ? 0 : 1;

      list<Potion*> :: iterator temp = potionsIterator++;
      delete (*temp);
      potions.erase(temp);
    }    
  }
}
void Hero::levelUp() {
	level++;			// These are common for all Heroes.
	strength += 10;
	agility += 10;
	dexterity += 10;
	magicPower += 5;
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
    throw HeroMoveException("You can't  down any further");
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
  switch (direction) {
  case UP: moveUp(); break;
  case DOWN: moveDown(); break;
  case LEFT: moveLeft(); break;
  case RIGHT: moveRight(); break;
  default: throw HeroMoveException("Unknown direction"); break; 
  }   
}

string Hero :: getUserInput(const string& prompt) {
  cout << prompt << endl << endl << "> ";

  string input;
  cin >> input;

  return input;
}

bool Hero :: equip(const string& name) {
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
      return false;
    }
    this->inventory.removeItem(itemToEquip);
    return true;
  }

  Spell* spellToEquip = inventory.getSpellByName(name);

  if (spellToEquip != NULL) {
    this->equipSpell(spellToEquip);
    this->inventory.removeSpell(spellToEquip);
    return true;
  }

  cout << "There's no such item or spell in your inventory" << endl;
  return false;
}

bool Hero :: discard(const string& name) {
  Item* itemToDiscard = inventory.getItemByName(name);

  if (itemToDiscard != NULL) {
    this->inventory.removeAndDeleteItem(itemToDiscard);
    return true;
  }

  Spell* spellToDiscard = inventory.getSpellByName(name);

  if (spellToDiscard != NULL) {
    this->inventory.removeAndDeleteSpell(spellToDiscard);
    return true;
  }

  cout << "There's no such item or spell in your inventory" << endl;
  return false;
}

bool Hero::use(const string& potionName) {
  // (George): Alternative implementation

  Potion* potionToUse = static_cast<Potion*>(inventory.getItemByName(potionName));
  if (potionToUse  == NULL) {
    cout << "This potion doesn't exist" << endl;
    return false;
  } else if (potionToUse->kindOf() != "Potion") {
    cout << "The item you selected isn't a Potion" << endl;
    return true;
  }
  potions.push_back(potionToUse);
  inventory.removeItem(potionToUse);
  this->strength *= potionToUse->getStrengthBoost() + 1.0;
  this->agility *= potionToUse->getAgilityBoost() + 1.0;
  this->dexterity *= potionToUse->getDexterityBoost() + 1.0;
  return true;
}

void Hero :: checkInventory() {
  this->inventory.getMenu().displayMenu();
  int selection;
  string equipPrompt = "Please enter the name of the item/spell you want to equip";
  string discardPrompt = "Please enter the name of the item/spell you want to discard";
  string usePotionPrompt = "Please enter the name of the potion you want to use";

  while ((selection = this->inventory.getMenu().getSelection())) {
    this->inventory.getMenu().clearMenu();
    switch (selection) {
    case 1: {
      this->inventory.printInfo();
      break;
    }
    case 2: {
      if (!this->getInventory().hasItems()) {
	cout << "You have no Items in your Inventory." << endl;
      } else {
	string input = getUserInput(equipPrompt);
	this->equip(input);
      }
      break;
    }
    case 3: {
      if (!this->getInventory().hasItems()) {
	cout << "There are no Items to discard." << endl;
      } else {
	string input = getUserInput(discardPrompt);
	this->discard(input);
      }
      break;      
    }
    case 4: {
      if (!this->getInventory().hasPotions()) {
	cout << "You have no Potions in your Inventory." << endl;
      } else {
	string input = getUserInput(usePotionPrompt);
	this->use(input);
      }
      break;
    } 
    case 5: {
      this->inventory.getMenu().clearMenu();
      return;
    }
    case 6: {
      handleQuitCase();
      this->inventory.getMenu().clearMenu();
      if (quitGame) return;      
      break;
    }
    }    
    this->inventory.getMenu().displayMenu();
  }
}

void Hero::buy(const string& itemName) {
  Market* currentMarket = this->getTile().getMarket();

  if (currentMarket == NULL) {
	  cout << "You can't buy on a tile that has no market!" << endl << endl;
	  return;
  }

  Item* itemToBuy = currentMarket->getItemByName(itemName);

  if (itemToBuy != NULL) {
    string kind = itemToBuy->kindOf();
    Item* itemToAdd;
    bool equiped = false;

    if (kind == "Weapon") {
      itemToAdd = new Weapon(*static_cast<Weapon*>(itemToBuy));
      Weapon* aux = static_cast<Weapon*>(itemToAdd);
      if (aux->needsBothHands()) {
        if (this->usesLeftHand() == false && this->usesRightHand() == false) {
	  this->equipWeapon(aux);
	  equiped = true;
	}
      } else {
	if (this->usesLeftHand() == false || this->usesRightHand() == false) {
	  this->equipWeapon(aux);
	  equiped = true;
	}
      }
    } else if (kind == "Armor") {
      itemToAdd = new Armor(*static_cast<Armor*>(itemToBuy));
      if (this->shield == NULL) {
	this->shield = static_cast<Armor*>(itemToAdd);
	equiped = true;
      }
    } else {
      itemToAdd = new Potion(*static_cast<Potion*>(itemToBuy));
      if (this->potions.size() == 0) {
	this->potions.push_back(static_cast<Potion*>(itemToAdd));
	equiped = true;
      }
    }

    if(!equiped) inventory.addItem(itemToAdd);
    money -= itemToBuy->buyFor();
    return;
  }

  Spell* spellToBuy = currentMarket->getSpellByName(itemName);
  
  if (spellToBuy != NULL) {
    string kind = spellToBuy->kindOf();
    Spell* spellToAdd;
    bool equiped = false;
    
    if (kind == "IceSpell") {
      spellToAdd = new IceSpell(*static_cast<IceSpell*>(spellToBuy));
    } else if (kind == "FireSpell") {
      spellToAdd = new FireSpell(*static_cast<FireSpell*>(spellToBuy));
    } else {
      spellToAdd = new LightningSpell(*static_cast<LightningSpell*>(spellToBuy));
    }
    if (this->spells.size() == 0) {
      this->spells.push_back(spellToAdd);
      equiped = true;
    }

    if (!equiped) inventory.addSpell(spellToAdd);
    money -= spellToBuy->getValue();
    return;
  }

  cout << "There's no item/spell with this name" << endl;
}

void Hero::sell(const string& itemName) {
    Item* itemToSell = inventory.getItemByName(itemName);

	if (itemToSell != NULL) {
		inventory.removeAndDeleteItem(itemToSell);
		money += itemToSell->sellsFor();
		return;
	}

	Spell* spellToSell = inventory.getSpellByName(itemName);
	if (spellToSell != NULL) {
		inventory.removeAndDeleteSpell(spellToSell);
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
      this->rightHandWeapon = weapon;
    } else {
      this->leftHandWeapon = weapon;
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

void Hero :: enterMarket(Market* market) {
  market->getMenu().displayMenu();
  int selection;
  string buyPrompt = "Please enter the name of the item/spell you want to buy";
  string sellPrompt = "Please enter the name of the item/spell you want to sell";

  while ((selection = market->getMenu().getSelection())) {   
    market->getMenu().clearMenu();
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
      if (!this->inventory.hasSpells() && !this->inventory.hasItems()) {
	cout << "You have no items or spells for sale" << endl;
	break;
      }
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
    case 5: {
      handleQuitCase();
      market->getMenu().clearMenu();
      if (quitGame) return;      
      break;
    }
    }
    market->getMenu().displayMenu();
  }
}

string Hero :: kindOf() const {
  return "Hero";
}

void Hero :: printEquipedSpells() const {
  list<Spell*> :: const_iterator it = spells.begin();
  for ( ; it != spells.end(); ++it) {
    cout << (*it)->getInfo() << endl;
  }
  cout << endl;
}

Spell* Hero :: getSpellByName(const string& name) {
  list<Spell*> :: const_iterator it = spells.begin();
  for ( ; it != spells.end(); ++it) {
    if ((*it)->getName() == name) {
      return *it;
    }
  }
  return NULL;
}

void Hero :: castSpell(Monster* target) {
  if (this->spells.empty()) {
    cout << "You have no spells for use" << endl;
    return;
  }
  cout << "You currently have these spells" << endl << endl;
  this->printEquipedSpells();
  Spell* spellToCast;
  do {
    cout << "Choose a spell to cast (name): ";
    string name;
    cin >> name;
    spellToCast = this->getSpellByName(name);
    if (spellToCast == NULL) {
      cout << "There's no such a spell" << endl;
    }
  } while (spellToCast == NULL);
  Random rng;
  double dodgeProbability = rng.from0to1();
  if (dodgeProbability <= target->getDodge()) {
    cout << "The monster dodged your attack" << endl;
    return;
  }
  int damage = this->dexterity +
    rng.fromMintoMax(spellToCast->getMinDamage(),
		     spellToCast->getMaxDamage());
  int damageReduction = target->getDamageReductionFactor() * damage;
  target->receiveDamage(damage - damageReduction);
  this->magicPower -= spellToCast->getMagicPowerRequired();
  this->magicPower = (this->magicPower < 0) ? 0 : this->magicPower;
  string kind = spellToCast->kindOf();
  if (kind == "FireSpell") {
    FireSpell* auxSpell = static_cast<FireSpell*>(spellToCast);
    int rounds = auxSpell->getReductionRounds();
    double amount = auxSpell->reduceOponentArmorBy();
    target->applyNerf(rounds, amount, Monster :: FIRE);
  } else if (kind == "IceSpell") {
    IceSpell* auxSpell = static_cast<IceSpell*>(spellToCast);
    int rounds = auxSpell->getReductionRounds();
    double amount = auxSpell->reduceOponentDamageRangeBy();
    target->applyNerf(rounds, amount, Monster :: ICE);    
  } else {
    LightningSpell* auxSpell = static_cast<LightningSpell*>(spellToCast);
    int rounds = auxSpell->getReductionRounds();
    double amount = auxSpell->reduceOponentDodgeBy();
    target->applyNerf(rounds, amount, Monster :: LIGHT);
  }
}

void Hero::attack(Monster* monster) {
	Random random;

	if (random.boolean(monster->getDodge())) {
	  cout << "Monster Dodged your attack sucker!" << endl;
		// Monster dodged this attack! , nothing happens.
	} else {
		int heroDamage = 0;
		// Calculate the damage that the Hero can cause.
		heroDamage += strength;

		if (leftHandWeapon != NULL) {
			heroDamage += leftHandWeapon->getDamage();
		}

		if (rightHandWeapon != NULL) {
			heroDamage += rightHandWeapon->getDamage();
		}

		// Calculate the damage reduction.
		int damageReduction = 0;

		damageReduction += monster->getDamageReductionFactor()*heroDamage;

		monster->receiveDamage(heroDamage - damageReduction);
	}
}

void Hero :: displayMap() const {
  this->grid->displayMap();
}

void Hero :: battle(list<Monster*>& monsters) {
  int selection;
  this->battleMenu.displayMenu();
  while ((selection = this->battleMenu.getSelection())) {
    this->battleMenu.clearMenu();
    switch (selection) {
    case 1: this->printStats(); break;
    case 2: this->printMonsters(monsters); break;
    case 3: handleAttackCase(monsters); return;
    case 4: handleCastSpellCase(monsters); return;
    case 5: if (handleUseCase()) return; break;
    case 6: if (handleEquipCase()) return; break;
    case 7: handleQuitCase(); if (quitGame) return;
            this->battleMenu.clearMenu(); break;
    }    
    this->battleMenu.displayMenu();
  }
}

void Hero :: printMonsters(list<Monster*>& monsters) {
  printMonsterFrame();
  cout << '|'
       << setw(14) << "NAME" << setw(11) << '|'
       << setw(7) << "LEVEL" << setw(3) << '|'
       << setw(5) << "HP" << setw(4) << '|'
       << setw(11) << "MIN DAMAGE" << setw(2) << '|'
       << setw(11) << "MAX DAMAGE" << setw(2) << '|'
       << setw(7) << "ARMOR" << setw(3) << '|'
       << setw(7) << "DODGE" << setw(3) << '|'
       << endl;
  list<Monster*> :: iterator it = monsters.begin();
  for ( ; it != monsters.end(); ++it) {
    (*it)->printStats();    
  }
  printMonsterFrame();
}

void Hero :: handleAttackCase(list<Monster*>& monsters) {
  Monster* monsterToAttack;

  if (monsters.size() == 1) {
    monsterToAttack = *monsters.begin();

    cout << "Attacking the only monster here: "
	 << monsterToAttack->getName() << endl;
  } else {
    do {
      monsterToAttack = NULL;
      cout << "Please enter the name of the monster you want to attack";
      cout << "(";
      list<Monster*> :: const_iterator it = monsters.begin();

      for ( ; it != monsters.end(); ++it) {
	cout << (*it)->getName();
	cout << ", ";
      }
      cout << ") : ";

      string name;
      cin >> name;

      for (it = monsters.begin() ; it != monsters.end(); ++it) {
	if ((*it)->getName() == name) {
	  monsterToAttack = (*it);
	  break;
	}
      }

    } while (monsterToAttack == NULL);

    cout << "Attacking Monster " << monsterToAttack->getName() << endl;
  }

  this->attack(monsterToAttack);

  if (monsterToAttack->getHealthPower() == 0) {
    ++this->monstersKilled;
    monsters.remove(monsterToAttack);
    delete monsterToAttack;
  }
}

void Hero :: handleCastSpellCase(list<Monster*>& monsters) {
  Monster* monsterToAttack;
  do {
    monsterToAttack = NULL;
    cout << "Please enter the name of the monster you want to cast spell: ";
    string name;
    cin >> name;
    list<Monster*> :: const_iterator it = monsters.begin();
    for ( ; it != monsters.end(); ++it) {
      if ((*it)->getName() == name) {
        monsterToAttack = (*it);
	break;
      }
    }
  } while (monsterToAttack == NULL);
  this->castSpell(monsterToAttack);
  if (monsterToAttack->getHealthPower() == 0) {
    monsters.remove(monsterToAttack);
    delete monsterToAttack;
  }
}

bool Hero :: handleUseCase() {
  if (!this->getInventory().hasPotions()) {
    cout << "You have no Potions at the moment." << endl;
    return false;
  }
  string name;
  do {
    cout << "Please enter the name of the potion you want to use: ";
    cin >> name;
  } while (this->use(name) == false);
  return true;
}

bool Hero :: handleEquipCase() {
  if (!this->getInventory().hasItems()) {
    cout << "You have no items in your Inventory." << endl;
    return false;
  }
  string name;
  do {
    cout << "Please enter the name of the weapon/armor you want to equip: ";
    cin >> name;
  } while (equip(name) == false);
  return true;
}
