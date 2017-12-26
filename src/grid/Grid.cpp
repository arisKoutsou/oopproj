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

movementReport Grid :: move(const Hero& hero, const string& direction) {
  // TODO (George): Wait for Aris to implement the functions that give
  // the position of the Hero and then finalize this implementation
  int heroX = hero.getX();
  int heroY = hero.getY();
  int numberOfLivings = tiles[heroY][heroX].numberOfLivings;

  if (direction == "up") {
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
  } else if (direction == "down") {
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
  } else if (direction == "left") {
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
  } else if (direction == "right") {
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
  } else {
    return directionError;
  }
}
