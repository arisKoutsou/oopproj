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
class Potion;

class Hero : public Living {
public:
        typedef enum {
	  NONE, STRENGTH, DEXTERITY, AGILITY
	} stats;

        typedef struct Nerfs {
	  Nerfs(int rounds = 0, double factor = 0.0, stats stat = NONE);
	  ~Nerfs();
	  int roundsNerfed;
	  double nerfFactor;
	  stats statNerfed;
	} Nerfs;

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
		double a = 0.2,
		int d = 100
	);
        ~Hero();
  
	double getAgility() const;
	int getDexterity() const;
	int getExpirience() const;
	int getMagicPower() const;
	int getMoney() const;
	int getStrength() const;
	double getDamageReductionFactor() const;
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
	void use(const string& potion);
	void enterMarket(Market* market);
	void buy(const string&);	// Add item, and subtract from money.
	void sell(const string&);	// Sells item, and gains money.
	Menu& getBattleMenu() const;
	void castSpell(Monster* target);
	void attack(Monster* monster);	// Reduces monster's health.
  
        // IMPROTANT: Call this function whenever a hero finishes his round.
	void nextRound();	// Checks potions and goes to next round.

protected:
	Weapon* leftHandWeapon;
	Weapon* rightHandWeapon;
	Armor* shield;
	Potion* potionInUse;
        list<Spell*> spells;
        //list<Potion*> potions;
        //list<Nerfs> nerfs;

        int 	roundsPlayed;   // Number of rounds played.
	int 	magicPower;	// Mana.
	int 	strength;
	double 	agility;	// P(dodge) an attack.
	int 	dexterity;
	int 	money;		// Gold.
	int 	expirience;	// Xp.

	Inventory inventory;	// Implemented by george.
                                // Contains all items and spells.
	Menu battleMenu;
        //bool nerfed;
private:
	void printEquipedSpells() const;
	Spell* getSpellByName(const string& name);
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
