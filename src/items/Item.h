/*
 * Item.h
 *
 *  Created on: Dec 26, 2017
 *      Author: aris
 */

#ifndef ITEMS_ITEM_H_
#define ITEMS_ITEM_H_

#include <string>
using namespace std;

class Item {
public:
	Item(
		string name,
		int val = 25,
		int s = 15,
		int minL = 3
	);
	virtual ~Item();

	string getName() const;		// Item's name...
	int sellsFor() const;		// Return how much it sells for.
	int buyFor() const;			// Return it's price.
	int unlocksInLevel() const;	// Return the level it unlocks.
        virtual string getInfo() const;		// Returns a string with all the info.

        // Added by: (George Liontos)
        bool operator==(const Item& rValue) const;
  
	const double sellRate = 0.5;// Sells for <sellRate>*buyFor().
private:
	string name;
	int value;
	int sellFor;
	int minLevel;
};

#endif /* ITEMS_ITEM_H_ */
