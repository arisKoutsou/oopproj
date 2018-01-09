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
#include <vector>

class Grid;
class Weapon;
class Armor;

class Hero : public Living {
public:
        // Added by: (George Liontos)

        // Posible directions for heros to move
        typedef enum {
	  UP, DOWN, LEFT, RIGHT
	} directions;

	Hero(
		string nam,
		int hp = 500,
		int mp = 200,
		int s = 100,
		int a = 250,
		int d = 100,
		int x = 0,
		int y = 0
	);

	int getAgility() const;
	int getDexterity() const;
	int getExpirience() const;
	int getMagicPower() const;

        int getMoney() const;
	int getStrength() const;
        void move(Grid& grid, directions direction) throw();
	virtual void levelUp() = 0;
	bool operator==(const Hero& rValue) const;
	// Opens the inventory menu and handles the hero selection
	void checkInventory();
	void equip(const string& name);
	void discard(const string& name);
	void usePotion(const string& name);

	void buy(const string&);	// Add item, and subtract from money.
	void sell(const string&);	// Sells item, and gains money.

protected:
  Weapon* leftHandWeapon;
  Weapon* rightHandWeapon;
  Armor* shield;
  vector<Spell*> spells;
  
	int 	magicPower;	// Mana.
	int 	strength;
	int 	agility;
	int 	dexterity;
	int 	money;		// Gold.
	int 	expirience;	// Xp.

	Inventory inventory;	// Implemented by george.
                                // Contains all items and spells.

        // Added by: (George Liontos)

        Grid* grid;
private:
        void moveUp(Grid& grid) throw();
        void moveDown(Grid& grid) throw();
        void moveLeft(Grid& grid) throw();
        void moveRight(Grid& grid) throw();
        string getUserInput();
};

#endif /* LIVINGS_HERO_H_ */
