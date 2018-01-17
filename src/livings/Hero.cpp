/*
 * Hero.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#include <cstring>
#include "Hero.h"

#include <iomanip>

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
	int y,
	int x,
	string nam,
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
  battleMenu(*this),
  shield(NULL),
  potionInUse(NULL),
  roundsPlayed(0)
{}

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

double Hero::getDamageReductionFactor() const {
	double result = 0.0;

	if (shield != NULL) {
		result += shield->getDamageReductionFactor();
	}

	return result;
}

const Grid::Tile& Hero::getTile() {
	return grid->getTile(
		getPosition().getY(),
		getPosition().getX()
	);
}

void Hero :: printStats() const {
	Living :: printStats();
	cout << setprecision(2);

	cout << "Mana: " << this->magicPower << endl
	   << "Strength: " << this->strength << endl
	   << "Agility: " << this->agility*100 << "%" << endl
	   << "Dexterity: " << this->dexterity << endl
	   << "Money: " << this->money << endl
	   << "Experience: " << this->expirience << endl;

	if (leftHandWeapon == NULL && rightHandWeapon == NULL) {
		cout << "Not using any weapon..." << endl << endl;
		return;
	}

	if (leftHandWeapon != NULL) {
		cout << "Left hand weapon: " << leftHandWeapon->getName() << endl;
	}

	if (rightHandWeapon != NULL) {
		cout << "Right hand weapon: " << rightHandWeapon->getName() << endl;
	}

	cout << endl;
}

void Hero::nextRound() {
  // (George): Alternative Implementation

  // list<Potion*> :: const_iterator potionsIterator = potions.begin();
  // list<Nerfs> :: const_iterator nerfsIterator = nerfs.begin();
  // for ( ; potionsIterator != potions.end(); ++potionsIterator) {
  //   (*potionsIterator)->roundPassed();
  //   if ((*potionsIterator)->getRoundsEffective() == 0) {
  //     this->strength /= (1 + potionInUse->getStrengthBoost());
  //     this->agility /= (1 + potionInUse->getAgilityBoost());
  //     this->dexterity /= (1 + potionInUse->getDexterityBoost());
  //     delete (*potionsIterator);
  //     potions.erase(potionsIterator);
  //   }
  // }
  // for ( ; nerfsIterator != nerfs.end(); ++nerfsIterator) {
  //   // NOTE (George) -> (Aris) Implement this the way you want the nerfs to behave
  // }
  // ++roundsPlayed;
  
	if (potionInUse != NULL) {
		potionInUse->roundPassed();

		if (potionInUse->getRoundsEffective() == 0) {
			this->strength /= (1 + potionInUse->getStrengthBoost());
			this->agility /= (1 + potionInUse->getAgilityBoost());
			this->dexterity /= (1 + potionInUse->getDexterityBoost());

			delete potionInUse;
			potionInUse = NULL;
		}
	}

	roundsPlayed++;
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

void Hero::use(const string& potionName) {
  // (George): Alternative implementation

  // Item* potionToUse = inventory.getItemByName(potionName);
  // if (potionToUse  == NULL) {
  //   cout << "This potion doesn't exist" << endl;
  //   return;
  // } else if (potionToUse->kindOf() != "Potion") {
  //   cout << "The item you selected isn't a Potion" << endl;
  //   return;
  // }
  // potions.push_back(static_cast<Potion*>(potionToUse));
  // inventory.removeItem(potionToUse);
  // this->strength *= (1 + potionInUse->getStrengthBoost());
  // this->agility *= (1 + potionInUse->getAgilityBoost());
  // this->dexterity *= (1 + potionInUse->getDexterityBoost());
  
	if (potionInUse != NULL) {
		cout << "You are already using a potion." << endl;
		return;
	} else {
		Item* searchItemResult = inventory.getItemByName(potionName);

		if (searchItemResult == NULL) {
			cout << "This Item doesn't exist!" << endl;
			return;
		}
		if (searchItemResult->kindOf() != "Potion") {
			cout << "The item you selected is not a Potion" << endl;
			return;
		}

		potionInUse = static_cast<Potion*>(searchItemResult);

		inventory.removeItem(searchItemResult);

		this->strength *= (1 + potionInUse->getStrengthBoost());
		this->agility *= (1 + potionInUse->getAgilityBoost());
		this->dexterity *= (1 + potionInUse->getDexterityBoost());

	}
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
      this->use(input);
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
  Market* currentMarket = this->getTile().getMarket();

  if (currentMarket == NULL) {
	  cout << "You can't buy on a tile that has no market!" << endl << endl;
	  return;
  }

  Item* itemToBuy = currentMarket->getItemByName(itemName);

  if (itemToBuy != NULL) {
    string kind = itemToBuy->kindOf();
    Item* itemToAdd;
    
    if (kind == "Weapon") {
      itemToAdd = new Weapon(*static_cast<Weapon*>(itemToBuy));
    } else if (kind == "Armor") {
      itemToAdd = new Armor(*static_cast<Armor*>(itemToBuy));
    } else {
      itemToAdd = new Potion(*static_cast<Potion*>(itemToBuy));
    }

    inventory.addItem(itemToAdd);
    money -= itemToBuy->buyFor();
    return;
  }

  Spell* spellToBuy = currentMarket->getSpellByName(itemName);
  
  if (spellToBuy != NULL) {
    string kind = spellToBuy->kindOf();
    Spell* spellToAdd;

    if (kind == "IceSpell") {
      spellToAdd = new IceSpell(*static_cast<IceSpell*>(spellToBuy));
    } else if (kind == "FireSpell") {
      spellToAdd = new FireSpell(*static_cast<FireSpell*>(spellToBuy));
    } else {
      spellToAdd = new LightningSpell(*static_cast<LightningSpell*>(spellToBuy));
    }

    inventory.addSpell(spellToAdd);
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
}

void Hero::attack(Monster* monster) {
	Random random;

	if (random.boolean(monster->getDodge())) {
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

Hero :: Nerfs :: Nerfs(int rounds, double factor, stats stat)

  : roundsNerfed(rounds), nerfFactor(factor), statNerfed(stat) {}

Hero :: Nerfs :: ~Nerfs() {}

int Hero :: Nerfs :: getRoundsNerfed() const {
  return roundsNerfed;
}

double Hero :: Nerfs :: getNerfFactor() const {
  return nerfFactor;
}

Hero :: stats Hero :: Nerfs :: getStatNerfed() const {
  return statNerfed;
}

void Hero :: Nerfs :: roundPassed() {
  --roundsNerfed;
}
