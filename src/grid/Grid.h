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
  struct Tile {
    Tile(int x, int y, bool nonAccessible, bool market,
	 bool common, bool hasLiving, int numberOfLivings);
    ~Tile();

    int getX() const;	// returns the x coordinate (col) of the tile
    int getY() const;	// returns the y coordinate (row) of the tile
    bool isNonAccessible() const; // returns if the tile is not accessible
    bool hasLiving() const;	  // returns if the tile has a living
    bool hasMarket() const;	  // returns if the tile has a market
    bool isCommon() const;	  // returns if the tile is common
    int getNumberOfLivings() const; // returns the number of livings
    Market getMarket() const;	    // returns the market of the tile
    
    int x;			// x represents the columns
    int y;			// y represents the rows
    bool nonAccessible;
    bool hasLiving;
    bool hasMarket;
    bool common;
    int numberOfLivings;
    vector<Market> market;
  };

  // Posible directions for heros to move
  enum directions = {
    up, down, left, right
  };

  // Error codes for reporting hero movement result
  enum movementReport = {
    success, upError, downError,
    leftError, rightError, directionError
  };
  
  // tileInfo is an array of bools which has 4 boolean values stored:
  // nonAccessible, hasMarket, common, hasLiving (with that order)
  Grid(int maxX, int maxY, bool[] tileInfo);
  ~Grid();

  int getMaxX() const;
  int getMaxY() const;
  
  // This function moves the hero to the required direction in the grid
  // and returns an enum value indicating if the movement succeded or not
  movementReport move(const Hero& hero, const directions& direction);
  vector<vector<Tile>> getTiles() const; // returns the all the tiles
  Tile getTile(int row, int col) const;  // returns the tile at row,col
  void addMarket(int row, int col, const Market& market);
private:
  int maxX;		        // max number of columns
  int maxY;			// max number of rows
  vector<vector<Tile>> tiles;
};

#endif
