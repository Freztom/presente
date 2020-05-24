#ifndef LEVEL_H
#define LEVEL_H

#define TILE_SIZE 48

#define WALL_HP 20
#define DEFAULT_HP 0

#define PORTAL_AMOUNT 4

/* A level is a matrix of cells, each cell is represented using chars.
'.' = free cells
'#' = walls
*/

//Now each cell will be a struct.
typedef struct {
    char name;
    // ID and position parameters can help towards interactions between cells.
    int id;
    int hp;
} cell;

typedef struct {
    int size_x, size_y;
    int link_portalx[PORTAL_AMOUNT];
    int link_portaly[PORTAL_AMOUNT];
    cell **cells;
} level;

// Create a new level with the given size, allocates memory for it.
level *level_new(int size_x, int size_y);

// Retrieves the cell at a given position, can be used for cells outside the board.
int level_get(const level *lvl, int x, int y);

// Put randomly placed walls of the given size in the level.
void level_fill_random(level *lvl, int wall_size);

// Destroy a level, free its memory.
void level_free(level *lvl);


#endif
