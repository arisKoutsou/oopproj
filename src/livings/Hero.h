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
#include "../menu/AllMenus.h"
#include "../grid/Grid.h"
#include <vector>

class Tile;
class Weapon;
class Armor;
class Monster;
class Potion;

class Hero : public Living {
public:
	// Added by: (George Liontos)
	// Posible directions for heros to move
        typedef enum {
	  UP, DOWN, LEFT,
	  RIGHT, UNKNOWN
	} directions;

	Hero(
		Grid* gr,
		string nam = "",
		int y = 0,
		int x = 0,
		int hp = 500,
		int mp = 200,
		int s = 100,
		double a = 0.2,
		int d = 100
	);
        ~Hero();

	double getAgility() const;
	int getDexterity() const;
	int getExperience() const;
	int getMagicPower() const;
	int getMaxMagicPower() const;
	int getMoney() const;
	int getStrength() const;
	double getDamageReductionFactor() const;
	int getExperienceMilestone() const;
	void nextMilestone();
	const Grid::Tile& getTile();	// Returns the Tile that Hero is on.
	void setMoney(int money);
	void setExperience(int experience);
	void setMagicPower(int mana);
	void move(directions direction);
	virtual void levelUp();
	string kindOf() const;
        void printStats() const;
	void displayMap() const;
	bool operator==(const Hero& rValue) const;
	// Opens the inventory menu and handles the hero selection
	void battle(list<Monster*>& monsters);
	void checkInventory();
	Inventory& getInventory();
	bool equip(const string& name);
	bool discard(const string& name);
	bool use(const string& potion);
	void enterMarket(Market* market);
	void buy(const string&);	// Add item, and subtract from money.
	void sell(const string&);	// Sells item, and gains money.
	BasicMenu& getGameMenu() ;
	void castSpell(Monster* target);
	void attack(Monster* monster);	// Reduces monster's health.

	// IMPROTANT: Call this function whenever a hero finishes his round.
        void updatePotions();	// Checks potions and goes to next round.
	int getMonstersKilled() const;
	void resetBattleStats();
	void respawn();

protected:
	Weapon* leftHandWeapon;
	Weapon* rightHandWeapon;
	Armor* shield;
	list<Spell*> spells;
	list<Potion*> potions;

	const int maxMagicPower;
	int 	magicPower;	// Mana.
	int 	strength;
	double 	agility;	// P(dodge) an attack.
	int 	dexterity;
	int 	money;		// Gold.
	int 	expirience;	// Xp
	int     monstersKilled;
	int 	milestone; 	// Experience to exceed for level-up.
	Inventory inventory;	// Implemented by george.
                                // Contains all items and spells.
        BattleMenu battleMenu;
        BasicMenu gameMenu;

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
	void handleAttackCase(list<Monster*>& monsters);
	void handleCastSpellCase(list<Monster*>& monsters);
        bool handleUseCase();
        bool handleEquipCase();
        void printMonsters(list<Monster*>& monsters);
};

#endif /* LIVINGS_HERO_H_ */
