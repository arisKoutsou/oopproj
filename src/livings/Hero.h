/*
 * Hero.h
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#ifndef LIVINGS_HERO_H_
#define LIVINGS_HERO_H_

#include "./Living.h"
#include "../inventory/Inventory.h"
#include "../menu/Menu.h"
#include "../grid/Grid.h"
#include <vector>

class Tile;
class Weapon;
class Armor;
class Monster;

class Hero : public Living {
public:
    // Added by: (George Liontos)
    // Posible directions for heros to move
	typedef enum {
		UP, DOWN, LEFT, RIGHT
	} directions;

	Hero(
		Grid* gr,
		int y = 0,
		int x = 0,
		string nam = "",
		int hp = 500,
		int mp = 200,
		int s = 100,
		int a = 250,
		int d = 100
	);
    ~Hero();
  
	int getAgility() const;
	int getDexterity() const;
	int getExpirience() const;
	int getMagicPower() const;
	int getMoney() const;
	int getStrength() const;
	const Grid::Tile& getTile();	// Returns the Tile that Hero is on.

    	void move(directions direction);
 	virtual void levelUp();
        string kindOf() const;
        void printStats() const;
	bool operator==(const Hero& rValue) const;
	// Opens the inventory menu and handles the hero selection
	void checkInventory();
	Inventory& getInventory();
	void equip(const string& name);
	void discard(const string& name);
	void usePotion(const string& name);
	void enterMarket(Market* market);
	void buy(const string&);	// Add item, and subtract from money.
	void sell(const string&);	// Sells item, and gains money.
        Menu& getBattleMenu() const;
        void castSpell(Monster* target);

    void attack(Monster* monster);	// Reduces monster's health.

protected:
	Weapon* leftHandWeapon;
	Weapon* rightHandWeapon;
	Armor* shield;
	list<Spell*> spells;

	int 	magicPower;	// Mana.
	int 	strength;
	int 	agility;
	int 	dexterity;
	int 	money;		// Gold.
	int 	expirience;	// Xp.

	Inventory inventory;	// Implemented by george.
							// Contains all items and spells.
        Menu battleMenu;

private:
	bool usesBothHands() const; // returns true if the hero uses both hands
	void equipWeapon(Weapon* weapon);
	void equipArmor(Armor* armor);
	void equipSpell(Spell* spell);
	bool usesOneHand() const;
	bool usesLeftHand() const;
	bool usesRightHand() const;
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	string getUserInput(const string& prompt);  
};

#endif /* LIVINGS_HERO_H_ */
