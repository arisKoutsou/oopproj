#include <iostream>
#include <fstream>

#include "random/Random.h"

#define NON_ACCESSIBLE_P 0.25
#define COMMON_P 0.3
#define MARKET_P 0.05
#define MIN_CAP 15
#define MAX_CAP 50

using namespace std;

int main(void) {
  int rows;
  int columns;
  cout << "Enter rows and columns: ";
  cin >> rows >> columns;
  Random rng;
  ofstream map("map.txt");
  if (map.is_open()) {
    map << "# Map goes as follows: Each line has information about a tile" << endl
	<< "# First value (true, false) is about nonAccessible" << endl
	<< "# Second value (true, false) is about common" << endl
	<< "# Third value (true, false) is about market. If it's true "
	<< "then an in is given which is the capacity of the market" << endl
	<< "# First line has the dimensions of the grid (row, col)" << endl
	<< "# The delimiter is ','" << endl << endl;
    map << rows << "," << columns << "," << endl << endl;
    for (size_t i = 0U; i != rows*columns*2; i += 2) {
      if (rng.boolean(NON_ACCESSIBLE_P)) map << "true,";
      else map << "false,";
      if (rng.boolean(COMMON_P)) map << "true,";
      else map << "false,";
      if (rng.boolean(MARKET_P)) {
	map << "true,";
	int cap = rng.fromMintoMax(MIN_CAP, MAX_CAP);
	map << cap << ",";
      } else map << "false,";
      map << endl;
    }
  }
  map.close();
  return 0;
}
