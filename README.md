# CLife
Implementing Conway's Game of Life in C, with raylib



# Compile with:
`gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`


* Current iteration takes on average 37ms per draw update cycle (using current configs of 500 x 500 grid, from the main version)
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



