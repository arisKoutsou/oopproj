/*
 * Living.h
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#ifndef LIVINGS_LIVING_H_
#define LIVINGS_LIVING_H_

#include  <string>

using namespace std;

class Grid;
class Menu;

class Living {
public:
	class Position {
	public:
		Position(int x, int y);
		~Position();

		void setX(int x);
		void setY(int y);
		int getX() const;
		int getY() const;

		bool operator==(const Position& rValue) const;
	private:
		int x;
		int y;
	};
  
	Living(		// Don't pass level as argument because at initialization it's 1.
	        Grid* gr,
		int y,
		int x,
	        string nam,
		int hp = 500
	);
	virtual ~Living();

	int getHealthPower() const;
        int getMaxHealthPower() const;
        int getLevel() const;
	const string& getName() const;  
	virtual void receiveDamage(int damageDealt);	// Subtract from hp the damageDealt.
	// Added by: (George Liontos)
	virtual void setHealthPower(int health);

	Position& getPosition();
        virtual void printStats() const;
	virtual string kindOf() const = 0;
	virtual bool operator==(const Living& rValue) const;

protected:
	Grid* 	grid;
	int 	level;			// Level starting from 0.
        int maxHealth;
private:
	Position p;
	string 	name;
	int 	healthPower;	// hp with a stupid name...       
};

#endif /* LIVINGS_LIVING_H_ */
