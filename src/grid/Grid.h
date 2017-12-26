// Grid.h --- 
// 
// Filename: Grid.h
// Author: George Liontos
// Created: Tue Dec 26 18:44:03 2017 (+0200)

#if !defined(__GRID_HEADER__)
#define __GRID_HEADER__

#include <iostream>
#include <vector>
#include "../hero/Hero.h"
#include "../market/Market.h"		// @Incomplete: Implement this

using namespace std;

class Grid {
public:
  // TODO (George): Make a decision about Tile constructor.
  // Should I pass as arguments the information that a market needs
  // or I should make another constructor that takes as argument a
  // market?
  struct Tile {
    Tile(int x, int y, bool nonAccessible, bool market,
	 bool common, bool hasLiving, int numberOfLivings);
    ~Tile();

    int x;			// x represents the columns
    int y;			// y represents the rows
    bool nonAccessible;
    bool hasLiving;
    bool hasMarket;
    bool common;
    int numberOfLivings;
    // We use this instead of pointer, meaning that
    // we are going to have at most one market
    vector<Market> market;	
  };

  enum movementReport = {
    success, upError, downError,
    leftError, rightError, directionError
  };
  
  // tileInfo is an array of bools which has 4 boolean values stored:
  // nonAccessible, hasMarket, common, hasLiving (with that order)
  Grid(int maxX, int maxY, bool[] tileInfo);
  ~Grid();
  // This function moves the hero to the required direction in the grid
  // and returns an enum value indicating if the movement succeded or not 
  movementReport move(const Hero& hero, const string& direction);
private:
  int maxX;		        // max number of columns
  int maxY;			// max number of rows
  vector<vector<Tile>> tiles;
};

#endif
