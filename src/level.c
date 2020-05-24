#include "level.h"

#include <stdlib.h>
#include <assert.h>

level *level_new(int size_x, int size_y){
    // Ask memory for the level struct
    level *lvl = malloc(sizeof(level));

    // Set the size
    lvl->size_x = size_x;
    lvl->size_y = size_y;

    // Ask memory for the cell* array - changed "char" to "cell"
    lvl->cells  = malloc(lvl->size_y * sizeof(cell *));

    // Ask memory for each row - changed "char" to "cell"
    for(int y=0;y<lvl->size_y;y++){
        lvl->cells[y] = malloc(lvl->size_x * sizeof(cell));
    }

    // Initialize level
    for(int y=0;y<lvl->size_y;y++){
        for(int x=0;x<lvl->size_x;x++){
            lvl->cells[y][x].name = '.';
            lvl->cells[y][x].hp = DEFAULT_HP;
        }
    }

    for(int i=0;i<PORTAL_AMOUNT;i++){
        lvl->link_portalx[i]=0;
        lvl->link_portaly[i]=0;
    }

    // Retreieve level's pointer
    return lvl;
}

int level_get(const level *lvl, int x, int y){
    // For cells outside the matrix:
    if(x<0) return 'W';
    if(y<0) return 'W';
    if(x>=lvl->size_x) return 'W';
    if(y>=lvl->size_y) return 'W';
    // Regular cells
    if(lvl->cells[y][x].name=='#' && lvl->cells[y][x].hp<=0){
        lvl->cells[y][x].hp=DEFAULT_HP;
        return '.';
    }
    return lvl->cells[y][x].name;
}

void level_fill_random(level *lvl, int wall_size){
    // Check that the wall_size is smaller than the level
    assert(wall_size<lvl->size_x);
    assert(wall_size<lvl->size_y);
    // Compute a good number of walls so that up to 1/10 of the level is filled
    int n_walls = lvl->size_x*lvl->size_y/wall_size/10;
    // Add each of the walls
    for(int i=0;i<n_walls;i++){
        int vert = rand()%2; // vertical or horizontal?
        if(vert){
            // Initial wall position
            int wx = rand()%(lvl->size_x);
            int wy = rand()%(lvl->size_y-wall_size);
            // Iterate to place wall vertically
            for(int k=0;k<wall_size;k++){
                lvl->cells[wy+k][wx].name = '#';
                lvl->cells[wy+k][wx].hp = WALL_HP;
            }
        }else{
            // Initial wall position
            int wx = rand()%(lvl->size_x-wall_size);
            int wy = rand()%(lvl->size_y);
            // Iterate to place wall horizontally
            for(int k=0;k<wall_size;k++){
                lvl->cells[wy][wx+k].name = '#';
                lvl->cells[wy][wx+k].hp = WALL_HP;
            }
        }
    }
    // Add portals
    int portals_built = 0;
    int contador_next=PORTAL_AMOUNT-1;
    while (portals_built<PORTAL_AMOUNT){
        int pwy = rand()%(lvl->size_y);
        int pwx = rand()%(lvl->size_x);
        if (lvl->cells[pwy][pwx].name=='.'){
            lvl->cells[pwy][pwx].name = 'P';
            lvl->cells[pwy][pwx].hp = DEFAULT_HP;
            lvl->cells[pwy][pwx].id = portals_built+5;
            lvl->link_portalx[contador_next]=pwx*TILE_SIZE+TILE_SIZE/2;
            lvl->link_portaly[contador_next]=pwy*TILE_SIZE+TILE_SIZE/2;
            if(portals_built==0) contador_next=0;
            else contador_next+=1;
            portals_built+=1;
        }
    }
}

// Free level memory
void level_free(level *lvl){
    // Free each row first
    for(int y=0;y<lvl->size_y;y++){
        free(lvl->cells[y]);
    }
    // Free char* array
    free(lvl->cells);
    // Free the level
    free(lvl);
}
