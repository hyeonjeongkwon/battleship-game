#include <stdbool.h>

// SEASHELL_READONLY

struct grid {
	bool cell[100];
	int total_ships[4];
};
// requires: 0 <= total_ships[i] <= 4 - i
// notes: A1 corresponds to cell[0*10 + 1]
//        J8 corresponds to cell[9*10 + 8]


// grid_get_cell(g, x, y) determines the status of a cell (x, y)
// note: returns  1 if (x, y) contains a boat
//       returns  0 if (x, y) does not contain a boat and within bounds
//       returns -1 if (x, y) is out of bounds
// examples: grid_get_cell(g, 0, 0) should return the status of the cell A0
//           grid_get_cell(g, 4, 5) should return the status of the cell F4
int grid_get_cell(const struct grid *g, int x, int y);


// grid_print(g) prints the grid g
void grid_print(const struct grid *g);


// grid_is_complete(g) checks if the grid g is complete or not
// notes: a grid is complete when it has exactly
//        1 ship of size 4
//        2 ships of size 3
//        3 ships of size 2
//        4 ships of size 1
//        otherwise it is called incomplete
// requires: g is valid [not asserted]
bool grid_is_complete(const struct grid *g);


// grid_add_ship(g, x, y, size, pos) adds a ship to the grid
// requires: g is valid [not asserted]
// notes: returns true if a ship was successfully placed
//        returns false if a ship cannot be placed
// examples: if a ship is out of bounds, returns false
//           if size < 1 or size > 4, returns false
//           if all ships of given size have been placed, returns false
//           if a grid becomes invalid once the ship is placed, returns false
// effects: modifies *g
bool grid_add_ship(struct grid *g, int x, int y, int size, bool orientation);
