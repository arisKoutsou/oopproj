#ifndef __GRID__
#define __GRID__

#include <iostream>

using namespace std;

class Grid {
public:
  struct Tile {
    Tile(bool accessible, bool market, bool common);
    ~Tile();
    bool accessible;
    bool market;
    bool common;
  };
  Grid(int maxx = 20U, int maxy = 20U);
  ~Grid();
private:
  const int maxx;
  const int maxy;
  Tile** grid_tiles;
};

#endif
