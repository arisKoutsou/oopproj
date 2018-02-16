
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
        virtual void getInfo() const;
        virtual string kindOf() const = 0;
        virtual bool operator==(const Item& rValue) const;   
private:
	string name;
	int value;
	int sellFor;
        int minLevel;
        const double sellRate; // Sells for <sellRate>*buyFor().
};

#endif /* ITEMS_ITEM_H_ */
