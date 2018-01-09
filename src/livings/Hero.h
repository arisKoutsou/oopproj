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

class Grid;

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

	void buy(string);	// Add item, and subtract from money.
	void sell(string);	// Sells item, and gains money.

protected:
	int 	magicPower;	// Mana.
	int 	strength;
	int 	agility;
	int 	dexterity;
	int 	money;		// Gold.
	int 	expirience;	// Xp.

	Inventory inventory;	// Implemented by george.
                                // Contains all items and spells.

        // Added by: (George Liontos)
  
        bool operator==(const Hero& rValue) const;
private:
        void moveUp(Grid& grid) throw();
        void moveDown(Grid& grid) throw();
        void moveLeft(Grid& grid) throw();
        void moveRight(Grid& grid) throw();
};

#endif /* LIVINGS_HERO_H_ */
