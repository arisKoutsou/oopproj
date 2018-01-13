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

class Living {
public:
    struct Position {
	  Position(int x, int y);
	  ~Position();

          void setX(int x);
          void setY(int y);
	  int getX() const;
	  int getY() const;
      
	  bool operator==(const Position& rValue) const;

	  int x;
	  int y;
	};
  
	Living(		// Don't pass level as argument because at initialization it's 1.
	        Grid* gr,
	        string nam,
		int hp = 500,
		int y = 0,
		int x = 0
	);
	virtual ~Living();
	int getHealthPower() const;
	int getLevel() const;
	const string& getName() const;
  
        // Added by: (George Liontos)
        Position& getPosition();
        virtual void printStats() const;
        virtual string kindOf() const = 0;
        virtual bool operator==(const Living& rValue) const;
protected:
        Grid* grid;
private:
	string 	name;
	int 	level;			// Level starting from 0.
	int 	healthPower;	// hp with a stupid name...
        Position p;

};

#endif /* LIVINGS_LIVING_H_ */
