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

class Living;
class Market;

using namespace std;

class Grid {
public:
  struct Tile {
    Tile(bool nonAccessible, bool common);
    ~Tile();

    bool isNonAccessible() const; // returns if the tile is not accessible
    bool hasLiving() const;	  // returns if the tile has a living
    bool hasMarket() const;	  // returns if the tile has a market
    bool isCommon() const;	  // returns if the tile is common
    bool isQualifiedForBattle(int numberOfHeroes) const; // returns if a battle can start at this tile
    int getNumberOfLivings() const; // returns the number of livings
    Market* getMarket() const;	    // returns the market of the tile
       
    bool nonAccessible;
    bool common;
    list<Living*> livings;
    Market* market;
  };
  
  // tileInfo is an array of bools which has 2 boolean values stored:
  // nonAccessible, common (with that order)
  Grid(int maxY, int maxX, bool* tileInfo);
  ~Grid();

  int getMaxX() const;
  int getMaxY() const;
  const Tile& getTile(int row, int col) const;  // returns the tile at row, col  
  // Adds a makret in tile which is at (row, col) location
  void addMarket(int row, int col, Market* market);
  // Adds a living (i.e Hero, Monster) at (row, col) location
  void addLiving(int row, int col, Living* living);
  // Removes a living (i.e Hero, Monster) from (row, col) location
  void removeLiving(int row, int col, Living* living);
  void displayMap() const;
private:
  int maxX;		        // max number of columns
  int maxY;			// max number of rows  
  vector<vector<Tile> > tiles;	// 2D grid of tiles
};

#endif
