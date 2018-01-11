// Grid.cpp --- 
// 
// Filename: Grid.cpp
// Author: George Liontos
// Created: Tue Dec 26 19:24:55 2017 (+0200)

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Grid.h"
#include "../market/Market.h"
#include "../livings/Living.h"

using namespace std;

Grid :: Tile :: Tile(bool _nonAccessible, bool _common)
  
  : nonAccessible(_nonAccessible), common(_common), market(NULL) {

//  cout << "Creating an instance of Tile" << endl;
}

Grid :: Tile :: ~Tile() {
  while (livings.empty() == false) {
    delete livings.front();
    livings.pop_front();
  }

  delete market;
  
//  cout << "Destroying a Tile" << endl;
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
  return common;
}

int Grid :: Tile :: getNumberOfLivings() const {
  return livings.size();
}

Market* Grid :: Tile :: getMarket() const {
  // NOTE (George): This function assumes that a market at
  // the specific tile exists
  return (market);	// (@aris) Return NULL if there is no market. That way we can be sure.
}

Grid :: Grid(int _maxX, int _maxY, bool* _tileInfo)

  : maxX(_maxX), maxY(_maxY), marketCount(0) {

  size_t auxI = 0U;
  size_t auxJ = 0U;
  
  for (ssize_t i = 0U; i != maxY; ++i) {
    vector<Tile> newTileVector;
    tiles.push_back(newTileVector);
    
    for (ssize_t j = 0U; j != maxX; ++j) {

      bool nonAccessible = _tileInfo[auxI + auxJ];
      bool common = _tileInfo[auxI + auxJ + 1];

      Tile newTile(nonAccessible, common);
      tiles[i].push_back(newTile);

      ++auxI;
      ++auxJ;
    }
  }

  cout << "Creating an instance of Grid" << endl;
}

Grid :: ~Grid() {
  cout << "Destroying a Grid" << endl;
}

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
  tiles[col][row].market = _market;
  marketCount++;
}

const Grid::Tile* Grid :: getTile(int row, int col) const {
   return &(tiles[row][col]);
}

void Grid :: addLiving(int row, int col, Living* living) {
  
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
  cout << endl;
  cout << "Displaying Grid..." << endl;
  cout << endl;

  for (ssize_t i = tiles.size() - 1; i >= 0; --i) {
    for (ssize_t j = 0; j != tiles[i].size(); ++j) {
      if (tiles[i][j].isNonAccessible()) {
	cout << "X";
      } else if (tiles[i][j].hasMarket()) {
	cout << "M";
      } else if (tiles[i][j].hasLiving()) {
	cout << "L";
      } else {
	cout << "+";
      }
    }
    cout << endl;
  }

  cout << endl;
}
