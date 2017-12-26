#include <iostream>
#include "grid.h"

using namespace std;

Grid :: Grid(int _maxx, int _maxy)
  : maxx(_maxx), maxy(_maxy) {


  grid_tiles = new Tile*[maxx * maxy];
  for (ssize_t i = 0U; i != (maxx * maxy); ++i) {
    grid_tiles[i] = new Tile(true, false, true);
  }
  cout << "Creating an instance of Grid" << endl;
}

Grid :: ~Grid() {
  for (ssize_t i = 0U; i != (maxx * maxy); ++i) {
    delete grid_tiles[i];
  } delete grid_tiles;
  cout << "Destroying a Grid" << endl;
}

Grid :: Tile :: Tile(bool _accessible, bool _market, bool _common)
  : accessible(_accessible), market(_market), common(_common) {

  cout << "Creating an instance of Tile" << endl;
}

Grid :: Tile :: ~Tile() { cout << "Destroying a Tile" << endl; }
