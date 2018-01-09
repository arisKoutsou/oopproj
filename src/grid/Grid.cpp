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
  
  : nonAccessible(_nonAccessible), common(_common) {

  cout << "Creating an instance of Tile" << endl;
}

Grid :: Tile :: ~Tile() {
  while (livings.empty() == false) {
    delete livings.front();
    livings.pop_front();
  }

  delete market;
  
  cout << "Destroying a Tile" << endl;
}

bool Grid :: Tile :: isNonAccessible() const {
  return nonAccessible;
}

bool Grid :: Tile :: hasLiving() const {
  return (livings.empty());
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

Market Grid :: Tile :: getMarket() const {
  // NOTE (George): This function assumes that a market at
  // the specific tile exists
  return (*market);
}

Grid :: Grid(int _maxX, int _maxY, bool* _tileInfo)

  : maxX(_maxX), maxY(_maxY) {

  size_t auxI = 0U;
  size_t auxJ = 0U;
  
  for (ssize_t i = 0U; i != maxY; ++i) {
    vector<Tile> newTileVector;
    tiles.push_back(newTileVector);
    
    for (ssize_t j = 0U; j != maxX; ++j) {

      bool nonAccessible = _tileInfo[auxI + auxJ];
      bool common = _tileInfo[auxI + auxJ + 1];

      int x = static_cast<int>(i);
      int y = static_cast<int>(j);
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
  if (tiles[row][col].market == NULL) {
    cerr << "You can't add more than one market in a tile" << endl;
    return;
  }
  // NOTE (George): We don't need copy constructor for this
  // as we don't have any pointers as data members
  tiles[row][col].market = _market;
}

Grid :: Tile Grid :: getTile(int row, int col) const {
   return (tiles[row][col]);
}

void Grid :: addLiving(int row, int col, Living* living) {
  tiles[row][col].livings.push_back(living);
}
 
void Grid :: removeLiving(int row, int col, Living* living) {
  tiles[row][col].livings.remove(living);
}

void Grid :: displayMap() const {
  size_t tileNumber = 0;
  for (size_t i = 0U; i != tiles.size(); ++i) {
    for (size_t j = 0U; j != tiles[i].size(); ++j) {
      cout << "Tile" << tileNumber << ":" << endl;
      cout << ((tiles[i][j].isNonAccessible()
		? "not accessible" : "accessible")) << endl;
        
      cout << ((tiles[i][j].hasLiving()
		? "has living" : "hasn't living")) << endl;

      cout << ((tiles[i][j].isCommon())
	       ? "is common" : "isn't common") << endl;
      tileNumber++;
    }
  }
}
