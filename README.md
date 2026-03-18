# CLife
Implementing Conway's Game of Life in C, with raylib



# Compile with:
`gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`










## Optimization status:
Approach 2. was choosen, doubling performance (more); Now 500x500 grid runs at 60fps.
Next obvious step:
* Make a list holding only the alive cells
    The way to make it render is to clearblackground, then draw all alive cells;
    Current setup need to check every cell in grid to find the alive ones...


## optimization start (Alpha 3 inProgress):
    updateGrid() drawGrid() 
    - Dish gridCells2, in place, we put, either:
        1. linked lists (say, linList):
            for each cell checked, if it should togle,
            store its coordinates in linList;
        * When done, update back gridCells (simply toggling
          each cell coord from linList);
        * Improve drawGrid so that it only draws cells 
          that change (using linList somehow);
        2. Instead of linList, allocate a big array(size
           equal to number of cells);
           Simillarly, for each cell checked in updateGrid(),
           if the cell should change, hold its coordinate in
           the array, keeping a counting var for the number
           of cells to change and using it as index in the
           array later (ignores stuff on the array bigger
           than the counting var's value).
    # Each approach should be tested
 



## Future Ideas:
* make a cell struct that holds cell poss, status and neighbours!
* improve update grid to only look close to alive cells
* make a list of alive cells only








* Current (alpha <= 2) iteration takes on average 37ms per draw update cycle (using current configs of 500 x 500 grid, from the main version)
* avg of 50ms on home setup
* Double the performance if not drawing rectangle black for dead cells. Causes cells never to be rendered as dead


## Previous versions (alpha) segment fault if grid size 900 x 900 (other values not tested)
## Now, with dynamic allocated matrix, it can take very big grid sizes!.
    Successfully run at 5000 x 5000, and dint crash, but dint run at 20k x 20k (it used 15gb of ram)
## No important performance changes
    


-> Changing Vector2 grid for dynamic allocated matrix.


#### checklist of updates
# Variables
- [X] cellNumber - Vector2
- [X] grid - matrix of Vector2 ?!
- [X] gridCells - matrix of int

# Functions
- [X] gridInit
- [X] gridCellsInit
- [X] updateGrid
- [X] countN
    - [X] Tooo much hardcode in the logic here...



