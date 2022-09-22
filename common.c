#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/*
 * Determines whether or not the room at [row][col] is a valid room within the
 *maze with dimensions num_rows x num_cols
 *
 * Parameters:
 *  - row: row of the current room
 *  - col: column of the current room
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *
 * Returns:
 *  - 0 if room is not in the maze, 1 if room is in the maze
 */
int is_in_range(int row, int col, int num_rows, int num_cols) {
    if(row >= 0 && col >= 0){
        if((row < num_rows) && (col < num_cols)){
            return 1;
        }
    }
    return 0;
    // TODO: implement function
}

/*
 * Given a pointer to the room and a Direction to travel in, return a pointer to
 *the room that neighbors the current room on the given Direction. For example:
 *get_neighbor(&maze[3][4], EAST) should return &maze[3][5]
 *
 * Parameters:
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - room: pointer to the current room
 *  - dir: Direction to get the neighbor from
 *  - maze: a 2D array of maze_room structs representing your maze
 * Returns:
 *  - pointer to the neighboring room
 */
struct maze_room *get_neighbor(int num_rows, int num_cols,
                               struct maze_room maze[num_rows][num_cols],
                               struct maze_room *room, Direction dir) {
        
        int currentRow = room->rows;
        int currentCol = room->cols;

        if(dir == NORTH){
            currentRow = currentRow - 1;
        }
        else if(dir == SOUTH){
            currentRow =  currentRow + 1;
        }
        else if(dir == WEST){
            currentCol = currentCol - 1;

        }
        else if(dir == EAST){
            currentCol = currentCol + 1; 
        }

        if(is_in_range(currentRow, currentCol, num_rows, num_cols)){
               return &maze[currentRow][currentCol]; 
        }
        else{
                return NULL; 
        }

    // TODO: implement function
}

/*
 * Initializes a 2D array of maze rooms with all of the necessary values
 *
 * Parameters:
 *  - num_rows: the number of the rows in the maze
 *  - num_cols: the number of columns in the maze
 *  - maze: a 2D array of uninitialized maze_rooms (to be initialized in
 *     this function)
 *
 * Returns: 
 *  - nothing (the initialized maze will be stored in the 'maze' array)
 */
void initialize_maze(int num_rows, int num_cols,
           struct maze_room maze[num_rows][num_cols]) {
            for (int r = 0; r < num_rows; r++){
                for(int c = 0; c < num_cols; c++){
                     maze[r][c].rows = r;
                     maze[r][c].cols = c;
                     maze[r][c].visited = 0;
                     maze[r][c].next = NULL;
                        for(int index = 0; index < 4; index++){
                                maze[r][c].connections[index] = 2;
                        }
                }
            }
    // TODO: implement function
}

