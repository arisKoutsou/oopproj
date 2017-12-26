#ifndef __GRID__
#define __GRID__

#include <iostream>
#include <cstdint>

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
  Grid(uint16_t maxx = 20U, uint16_t maxy = 20U);
  ~Grid();
private:
  const uint16_t maxx;
  const uint16_t maxy;
  Tile** grid_tiles;
};

#endif
