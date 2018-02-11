// Grid.cpp --- 
// 
// Filename: Grid.cpp
// Author: George Liontos
// Created: Tue Dec 26 19:24:55 2017 (+0200)

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "Grid.h"
#include "../market/Market.h"
#include "../livings/Living.h"

using namespace std;

Grid :: Tile :: Tile(bool _nonAccessible, bool _common)
  
  : nonAccessible(_nonAccessible), common(_common), market(NULL) {}

Grid :: Tile :: ~Tile() {
  while (livings.empty() == false) {
    delete livings.front();
    livings.pop_front();
  }

  delete market;
}

bool Grid :: Tile :: isNonAccessible() const {
  return nonAccessible;
}

bool Grid :: Tile :: hasLiving() const {
  return !livings.empty();	// fixed, "!" missing.
}

bool Grid :: Tile :: hasMarket() const {
  return (market != NULL);
}

bool Grid :: Tile :: isCommon() const {
  return common == true;
}

bool Grid :: Tile :: isQualifiedForBattle(int numberOfHeroes) const {
  return ((livings.size() == numberOfHeroes && common));
}

int Grid :: Tile :: getNumberOfLivings() const {
  return livings.size();
}

Market* Grid :: Tile :: getMarket() const {
  // NOTE (George): This function assumes that a market at
  // the specific tile exists
  return (market);	// (@aris) Return NULL if there is no market. That way we can be sure.
}
/* Temporarily removed... didnt compile...
const list<Living*>& Grid :: Tile :: getLivings() const {
  return this->livings;
}
*/

Grid :: Grid(int _maxY, int _maxX, bool* _tileInfo)

  : maxX(_maxX), maxY(_maxY), marketCount(0) {

  size_t auxI = 0U;
  
  for (size_t i = 0U; i != maxY; ++i) {
    vector<Tile> newTileVector;
    tiles.push_back(newTileVector);
    
    for (size_t j = 0U; j != maxX; ++j) {

      bool nonAccessible = _tileInfo[auxI];
      bool common = _tileInfo[auxI + 1];

      Tile newTile(nonAccessible, common);
      tiles[i].push_back(newTile);
      
      auxI += 2U;
    }
  }
}

Grid :: ~Grid() {}

int Grid :: getMaxX() const {
  return maxX;
}

int Grid :: getMaxY() const {
  return maxY;
}
 
void Grid :: addMarket(int row, int col, Market* _market) {
  if (tiles[row][col].hasMarket()) {	// market == NULL means there is no market at that tile.
    cerr << "You can't add more than one market in a tile." << endl;
    return;
  }
  // (@aris)
  if (tiles[row][col].isNonAccessible()) {	// If it's non accessible u cant put a market in it.
	  cerr << "You can't add a market at a nonAccessible tile." << endl;
	  return;
  }
  // NOTE (George): We don't need copy constructor for this
  // as we don't have any pointers as data members
  tiles[row][col].market = _market;
  marketCount++;
}


const Grid :: Tile& Grid :: getTile(int row, int col) const {
  return (tiles[row][col]);
}   

void Grid :: addLiving(int row, int col, Living* living) {
  list<Living*> :: const_iterator it = tiles[row][col].livings.begin();
  for ( ; it != tiles[row][col].livings.end(); ++it) {
    if ((*it) == living) {
      return;
    }
  }  
  if (tiles[row][col].isNonAccessible()) {
    cerr << "A Hero can't be on a nonAccessible Tile." << endl;
    return;
  }
  tiles[row][col].livings.push_back(living);
}
 
void Grid :: removeLiving(int row, int col, Living* living) {
  tiles[row][col].livings.remove(living);
}

// (@aris) Implemented displayMap function.
// Prints "+" and letters to represent grid.
void Grid :: displayMap() const {

	int columns = tiles[0].size();	// Get the size of the vector of tiles.
	int rows = tiles.size();		// Get the size of lines of the vector.

	// Draw the first line which is a wall...
	for (int i = 0; i < columns; i++) {
		cout << "+---";
	}
	cout << "+" << endl;

	for (int i = rows; i >= 0 ; i--) {
		// Draw | H |   | ....
		for (int j = 0; j < columns; j++) {
			cout << "|";

			if (tiles[i][j].hasLiving()) {
				cout << " H ";
			} else if (tiles[i][j].hasMarket()) {
				cout << " M ";
			} else if (tiles[i][j].isNonAccessible()) {
				cout << "###";
			} else if (tiles[i][j].isCommon()) {
				cout << " C ";
			} else {
				cout << "   ";
			}

		}
		cout << "|" << endl;

		// Draw wall...
		for (int i = 0; i < columns; i++) {
			cout << "+---";
		}
		cout << "+" << endl;
	}

}






