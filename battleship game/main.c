// This is a simple I/O driver client for the grid module

#include <stdio.h>
#include <assert.h>

#include "grid.h"

extern const bool HORIZONTAL;
extern const bool VERTICAL;

int main(void) {
  char letter = '\0';
  int x = 0;
  int y = 0;
  int size = 0;
  char orientation = '\0';
  bool ship_placed = false;
  
  struct grid g = {0};
  
  while (scanf(" %c", &letter) == 1) {
    
    if (letter == 'S') {
      grid_print(&g);
      printf("THE GRID IS ");
      if (grid_is_complete(&g)) {
        printf("COMPLETE\n");
      } else {
        printf("INCOMPLETE\n");
      }
      continue;
    }
    
    if (letter < 'A' || letter > 'J') {
      break;
    }
    
    y = letter - 'A';
    
    assert(scanf("%d", &x) == 1);
    assert(0 <= x && x <= 9);
 
    assert(scanf("%d", &size) == 1);
    assert(1 <= size && size <= 4);
    
    assert(scanf(" %c", &orientation) == 1);
    assert(orientation == 'H' || orientation == 'V');
    
    if (orientation == 'H') {
      ship_placed = grid_add_ship(&g, x, y, size, HORIZONTAL);
    } else {
      ship_placed = grid_add_ship(&g, x, y, size, VERTICAL);
    }
    
    if (ship_placed == true) {
      printf("%c%d: success\n", letter, x);
    } else {
      printf("%c%d: unable to place the ship\n", letter, x);
    }
  }
}
