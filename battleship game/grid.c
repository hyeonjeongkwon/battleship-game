#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

const bool HORIZONTAL = false;
const bool VERTICAL = true;




// see grid.h for details
int grid_get_cell(const struct grid *g, int x, int y) {
  assert(g);

  int point = y * 10 + x;
  if (x < 0 || x > 9) {
    return -1;
  } else if (y < 0 || x > 9) {
    return -1;
  } else if (g->cell[point] == true) {
    return 1;
  } else {
    return 0;
  }
}




// see grid.h for details
void grid_print(const struct grid *g) {
  assert(g);

  char alpha = 'A';
  int num = 0;

  printf("  ");
  for (int i = 0; i < 10; ++i) {
    printf(" ");
    printf("%d", num);
    ++num;
  }
  for (int i = 0; i < 100; ++i) {
    if (i % 10 == 0) {
      printf("\n");
      printf("%c |", alpha);
      ++alpha;
    }
    if (g->cell[i] == true) {
      printf("x");
    } else {
      printf(" ");
    }
    printf("|");
  }
  printf("\n");
}




// see grid.h for details
bool grid_is_complete(const struct grid *g) {
  assert(g);

  if (g->total_ships[0] == 4 && g->total_ships[1] == 3 &&
      g->total_ships[2] == 2 && g->total_ships[3] == 1) {
    return true;
  }
  return false;
}




// is_invalid(g, x, y, size, orientation) checks if a grid g 
//  becomes invalid once the ship is placed according to the 
//  initial position of x and y, size and orientation
// requires: g is valid [not asserted]
// effects: may modify x or y 
static bool is_invalid
  (struct grid *g, int x, int y, int size, bool orientation) {
  assert(g);
  assert(0 <= x && x <= 9);
  assert(0 <= y && y <= 9);

  bool check = true;
  int current = 0;
  for (int i = 0; i < size; ++i) {
    current = y * 10 + x;

    if (y == 0 && x == 0) {
      //checks the adjacent cells when at A0
      if (g->cell[current] == true || 
          g->cell[current + 1] == true ||
          g->cell[current + 10] == true ||
          g->cell[current + 11] == true) {
        check = false;
        break;
      }
    } else if (y == 0 && x == 9) {
      // checks the adjacent cells when at A9
      if (g->cell[current] == true || 
          g->cell[current - 1] == true ||
          g->cell[current + 10] == true ||
          g->cell[current + 9] == true) {
        check = false;
        break;
      }
    } else if (y == 9 && x == 0) {
      // checks the adjacent cells when at J0
      if (g->cell[current] == true ||
          g->cell[current - 10] == true ||
          g->cell[current - 9] == true ||
          g->cell[current + 1] == true) {
        check = false;
        break;
      }
    } else if (y == 9 && x == 9) {
      // checks the adjacent cells when at J9
      if (g->cell[current] == true ||
          g->cell[current - 10] == true ||
          g->cell[current - 1] == true ||
          g->cell[current - 11] == true) {
        check = false;
        break;
      }
    } else if (x == 0) {
      // checks the adjacent cells when in the first column 
      //   and not A0 or J0
      if (g->cell[current] == true || 
          g->cell[current + 1] == true ||
          g->cell[current - 10] == true ||
          g->cell[current + 10] == true ||
          g->cell[current - 9] == true ||
          g->cell[current + 11] == true) {
        check = false;
        break;
      }
    } else if (x == 9) {
      // checks the adjacent cells when in the last column 
      //   and not A9 or J9
      if (g->cell[current] == true || 
          g->cell[current - 1] == true ||
          g->cell[current - 10] == true ||
          g->cell[current + 10] == true ||
          g->cell[current + 9] == true ||
          g->cell[current - 11] == true) {
        check = false;
        break;
      }
    } else if (y == 0) {
      // checks the adjacent cells when in the first row 
      //   and not A0 or A9
      if (g->cell[current] == true || 
          g->cell[current + 1] == true ||
          g->cell[current - 1] == true ||
          g->cell[current + 10] == true ||
          g->cell[current + 11] == true ||
          g->cell[current + 9] == true) {
        check = false;
        break;
      }
    } else if (y == 9) {
      // checks the adjacent cells when in the first row 
      //   and not J0 or J9
      if (g->cell[current] == true || 
          g->cell[current + 1] == true ||
          g->cell[current - 1] == true ||
          g->cell[current - 10] == true ||
          g->cell[current - 11] == true ||
          g->cell[current - 9] == true) {
        check = false;
        break;
      }
    } else {
      // checks the adjacent cells when not on the edges
      if (g->cell[current] == true || 
          g->cell[current - 1] == true ||
          g->cell[current + 1] == true ||
          g->cell[current - 10] == true ||
          g->cell[current - 11] == true ||
          g->cell[current - 9] == true ||
          g->cell[current + 10] == true ||
          g->cell[current + 11] == true ||
          g->cell[current + 9] == true) {
        check = false;
        break;
      }
    }

    if (orientation == HORIZONTAL) {
      x += 1;
    } else {
      y += 1;
    }
  }
  return check;
}




//place_ship(g, x, y, size, orientation) adds a ship to the grid g
//  according to the initial position x and y, size, and the
//  orientation
// requires: g is valid [not asserted]
// effects: modifies *g
static void place_ship 
  (struct grid *g, int x, int y, int size, bool orientation) {
  assert(g);
  assert(0 <= x && x <= 9);
  assert(0 <= y && y <= 9);
  
  if (orientation == HORIZONTAL)
    for (int i = 0; i < size; ++i) {
      int cell_num = y * 10 + x;
      g->cell[cell_num] = true;
      x += 1;
    }
  else {
    for (int i = 0; i < size; ++i) {
      int cell_num = y * 10 + x;
      g->cell[cell_num] = true;
      y += 1;
    }
  }
  g->total_ships[size - 1] += 1;
}




// see grid.h for details
bool grid_add_ship(struct grid *g, int x, int y, int size, bool orientation) {
  assert(g);

  if (x > 9 || x < 0) {
    return false;
  }

  if (y > 9 || y < 0) {
    return false;
  }

  if ((g->total_ships[size - 1] + size) == 5) {
    // size and the max number of that size of battleships always 
    //   equal to 5
    return false;
  }

  if (size < 1 || size > 4) {
    return false;
  }

  if (orientation == VERTICAL && y + size - 1 > 9) {
    // becomes out of bound vertically
    return false;
  }

  if (orientation == HORIZONTAL && x + size - 1 > 9) {
    // becomes out of bound vertically
    return false;
  }

  if (!is_invalid(g , x, y, size, orientation)) {
    return false;
  } 

  place_ship(g, x, y, size, orientation);
  return true;
}
