// Grid.h --- 
// 
// Filename: Grid.h
// Author: George Liontos
// Created: Tue Dec 26 18:44:03 2017 (+0200)

#if !defined(__GRID_HEADER__)
#define __GRID_HEADER__

#include <iostream>
#include <list>
#include <vector>
#include "../livings/Hero.h"
#include "../market/Market.h"

class Living;

using namespace std;

class Grid {
public:
  struct Tile {
    Tile(int x, int y, bool nonAccessible, bool market,
	 bool common, bool hasLiving);
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
    bool _hasLiving;
    bool _hasMarket;
    bool common;
    list<Living*> livings;
    vector<Market> market;
  };
  
  // tileInfo is an array of bools which has 4 boolean values stored:
  // nonAccessible, hasMarket, common, hasLiving (with that order)
  Grid(int maxX, int maxY, bool* tileInfo);
  ~Grid();

  int getMaxX() const;
  int getMaxY() const;

  vector<vector<Tile> > getTiles() const; // returns the all the tiles
  Tile getTile(int row, int col) const;  // returns the tile at row, col

  // Adds a makret in tile which is at (row, col) location
  void addMarket(int row, int col, const Market& market);

  // Adds a living (i.e Hero, Monster) at (row, col) location
  void addLiving(int row, int col, Living* living);

  // Removes a living (i.e Hero, Monster) from (row, col) location
  void removeLiving(int row, int col, Living* living);

  // Displays the map
  void displayMap() const;
private:
  int maxX;		        // max number of columns
  int maxY;			// max number of rows
  vector<vector<Tile> > tiles;	// 2D grid of tiles
};

#endif
