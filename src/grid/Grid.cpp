// Grid.cpp --- 
// 
// Filename: Grid.cpp
// Author: George Liontos
// Created: Tue Dec 26 19:24:55 2017 (+0200)

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Grid.h"

using namespace std;

Grid :: Tile :: Tile(int _x, int _y, bool _nonAccessible,
		     bool _hasMarket, bool _common, bool _hasLiving,
		     int _numberOfLivings)
  
  : x(_x), y(_y), nonAccessible(_nonAccessible), hasMarket(_hasMarket),
    common(_common), hasLiving(_hasLiving),
    numberOfLivings(_numberOfLivings) {

  cout << "Creating an instance of Tile" << endl;
}

Grid :: Tile :: ~Tile() {
  cout << "Destroying a Tile" << endl;
}

int Grid :: Tile :: getX() const {
  return x;
}

int Grid :: Tile :: getY() const {
  return y;
}

bool Grid :: Tile :: isNonAccessible() const {
  return nonAccessible;
}

bool Grid :: Tile :: hasLiving() const {
  return hasLiving;
}

bool Grid :: Tile :: hasMarket() const {
  return hasMarket;
}

bool Grid :: Tile :: isCommon() const {
  return common;
}

int Grid :: Tile :: getNumberOfLivings() const {
  return numberOfLivings;
}

Market Grid :: Tile :: getMarket() const {
  // NOTE (George): This function assumes that a market at
  // the specific tile exists
  return (market[0]);
}

Grid :: Grid(int _maxX, int _maxY, bool[] _tileInfo)

  : maxX(_maxX), maxY(_maxY) {

  size_t auxI = 0U;
  size_t auxJ = 0U;
  
  for (size_t i = 0U; i != maxY; ++i) {

    for (size_t j = 0U; j != maxX; ++j) {

      bool nonAccessible = _tileInfo[auxI + auxJ];
      bool hasMarket = _tileInfo[auxI + auxJ + 1];
      bool common = _tileInfo[auxI + auxJ + 2];
      bool hasLiving = _tileInfo[auxI + auxJ + 3];

      int x = static_cast<int>(i);
      int y = static_cast<int>(j);
      Tile newTile(x, y, nonAccessible, hasMarket, common, hasLiving);
      tiles.push_back(newTile);

      ++auxI;
      ++auxJ;
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
 
void Grid :: addMarket(int row, int col, const Market _market) {
  if (tiles[row][col].market.empty() == false) {
    cerr << "You can't add more than one market in a tile" << endl;
    return;
  }
  // NOTE (George): We don't need copy constructor for this
  // as we don't have any pointers as data members
  tiles[row][col].market.push_back(_market);
}

Tile Grid :: getTile(int row, int col) const {
   return (tiles[row][col]);
}
 
movementReport Grid :: move(const Hero& hero, const directions& direction) {
  // TODO (George): Wait for Aris to implement the functions that give
  // the position of the Hero and then finalize this implementation
  int heroX = hero.getX();
  int heroY = hero.getY();
  int numberOfLivings = tiles[heroY][heroX].numberOfLivings;

  switch (direction) {
  case up: {
    if (heroY ==  maxY) {
      return upError;
    } else {
      hero.setY(heroY + 1);

      if (numberOfLivings ==  1) {
	tiles[heroY][heroX].hasLiving = false;
      }

      --tiles[heroY][heroX].numberOfLivings;
      tiles[heroY + 1][heroX].hasLiving = true;

      return success;
    }
  }

  case down: {
    if (heroY == 0) {
      return downError;
    } else {
      hero.setY(heroY - 1);

      if (numberOfLivings == 1) {
	tiles[heroY][heroX] = false;
      }

      --tiles[heroY][heroX].numberOfLivings;
      tiles[heroY - 1][heroX].hasLiving = true;

      return success;
    }
  }

  case left: {
    if (heroX == 0) {
      return leftError;
    } else {
      hero.setX(heroX - 1);

      if (numberOfLivings == 1) {
	tiles[heroY][heroX] = false;
      }

      --tiles[heroY][heroX].numberOfLivings;
      tiles[heroY][heroX + 1].hasLiving = true;

      return success;
    }
  }

  case right: {
    if (heroX == maxX) {
      return rightError;
    } else {
      hero.setX(heroX + 1);

      if (numberOfLivings == 1) {
	tiles[heroY][heroX] = false;
      }

      --tiles[heroY][heroX].numberOfLivings;
      tiles[heroY][heroX + 1].hasLiving = true;

      return success;
    }
  }

  defaut: return directionError;
  }
}
