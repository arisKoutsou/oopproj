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

class Living {
public:
	Living(		// Don't pass level as argument because at initialization it's 1.
		string nam,
		int hp = 500
	);
	virtual ~Living();
	int getHealthPower() const;
	int getLevel() const;
	const string& getName() const;

private:
	string 	name;
	int 	level;			// Level starting from 1.
	int 	healthPower;	// hp with a stupid name...

};

#endif /* LIVINGS_LIVING_H_ */
