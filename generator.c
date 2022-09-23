#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generator.h"
/*
 * Given a direction, get its opposite
 *
 * Parameters:
 *  - dir: direction
 *
 * Returns:
 *  - the opposite direction to dir
 */
Direction get_opposite_dir(Direction dir) {
    if(dir == NORTH){
        return SOUTH;
    }
    else if(dir == SOUTH){
        return NORTH;
    }
    else if(dir == WEST){
        return EAST;
    }
    else if(dir == EAST){
        return WEST;
    }
    else{
        fprintf(stderr, "ERROR\n");
        assert(0);
    }
    // TODO: implement this function
}

/*
 * Given an array of the four directions, randomizes the order of the directions
 *
 * Parameters:
 *  - directions: an array of Direction enums of size 4
 *
 * Returns:
 *  - nothing - the array should be shuffled in place
 */

void swap(Direction *i, Direction *j){
    Direction temp;
    temp = *j; *j = *i; *i = temp;
}
void shuffle_array(Direction directions[]) {

    for(int i = 0; i < 4; i++){
        int r = (i + (rand() % (4 - i)));
        Direction temp; 
        temp = directions[r]; 
        directions[r] = directions[i];
        directions[i] =  temp;
        //swap(&directions[i], &directions[r]);
    }
    // TODO: implement this function
}

/*
 * Recursive function for stepping through a maze and setting its
 *connections/walls using the drunken_walk algorithm
 *
 * Parameters:
 *  - row: row of the current room
 *  - col: column of the current room
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - maze: a 2D array of maze_room structs representing your maze
 * Returns:
 *  - nothing - the state of your maze should be saved in the maze array
 *being passed in (make sure to use pointers correctly!).
 */



 /*
 drunken_walk(row, col):
    set r as the room at (row, col) 
    mark r as visited
    for each direction dir in random order:
 set n as the neighbor in direction dir
 if n is out of bounds:
store a wall in r at direction dir
        else:
            if n has not yet been visited:
                store an opening in r at direction dir
                perform drunken walk on n
            else: 
                if n has a wall or opening in the direction opposite of dir:
                    store that value in r at direction dir
                else:
                    store a wall in r at direction dir

 */

int check_range(int row, int col, int num_rows, int num_cols, Direction dir) {
        if(dir == NORTH){
            row--;
        }
        else if(dir == SOUTH){
            row++;
        }
        else if(dir == WEST){
            col--;

        }
        else if(dir == EAST){
            col++; 
        }

    if(row >= 0 && col >= 0){
        if((row < num_rows) && (col < num_cols)){
            return 1;
        }
    }
    return 0;
    // TODO: implement function
}

 void intSwap(int *i, int *j){
    int temp;
    temp = *j; *j = *i; *i = temp;
}

void drunken_walk(int row, int col, int num_rows, int num_cols,
                  struct maze_room maze[num_rows][num_cols]) {
            struct maze_room *r = &maze[row][col];
            r->visited = 1;
            Direction directions[4] = {NORTH, SOUTH, WEST, EAST}; 
            shuffle_array(directions); 
            for(int i = 0; i < 4; i++){
                Direction dir = directions[i]; // r.connection[i] = dir
                struct maze_room *n = get_neighbor(num_rows, num_cols, maze, r, dir); 
                if(check_range(r->rows, r->cols, num_rows, num_cols, dir) == 0){
                    r->connections[dir] = 1;
                }
                    else
                    {
                        if(n->visited == 0){
                        r->connections[dir] = 0; 
                        drunken_walk(n->rows, n->cols, num_rows, num_cols, maze);
                        }
                        else{
                            if(n->connections[get_opposite_dir(dir)] == 0 || n->connections[get_opposite_dir(dir)] == 1){
                            r->connections[dir] = n->connections[get_opposite_dir(dir)]; 
                            }
                            else{
                            r->connections[dir] = 1;
                            }
                        }
                    }
            }
    // TODO: implement this function
}

//Helper method required to get the array from most important to least? 

/*
 * Represents a maze_room struct as an integer based on its connections
 *
 * Parameters:
 *  - room: a struct maze_room to be converted to an integer
 *
 * Returns:
 *  - the integer representation of a room
 */

 void shift_room(int directions[]){
    // North South West East -> East West South North
    // 1010

    for(int i = 0; i < 2; i++){
        int temp;
        int dir = 3 - i; 
        temp = directions[dir];
        directions[dir] = directions[i]; 
        directions[i] = temp; 
    }
 }

int encode_room(struct maze_room room) {
    // TODO: implement this function
         int sum = 0;
        // Direction directions[4] = {NORTH, SOUTH, WEST, EAST}; 
         shift_room(room.connections); 
    for(int i = 3; i >= 0; i--){
        if(room.connections[i] == 1){
           if(i == 0){
                sum += 8;
           }
           if(i == 1){
                sum += 4;
           }
           if(i == 2){
                sum += 2;
           }
           if(i == 3){
                sum += 1;
           }
        }
    }
    return sum; 
 
}

/*
 * Represents a maze_room array as a hexadecimal array based on its connections
 *
 * Parameters:
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - maze: a 2D array of maze_room structs representing the maze
 *  - result: a 2D array of integers representing the maze
 *
 * Returns:
 *  - nothing - each maze_room in the maze should be represented
 *    as an integer [0, 15] and put in nums at the corresponding index
 */
void encode_maze(int num_rows, int num_cols,
                 struct maze_room maze[num_rows][num_cols],
                 int result[num_rows][num_cols]) {
                    for(int r = 0; r < num_rows; r++){
                        for(int c = 0; c < num_cols; c++){
                            result[r][c] = encode_room(maze[r][c]); 
                        }
                    }
            
    // TODO: implement this function
}

/*
 * Writes encoded maze to an output file
 *
 * Parameters:
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - encoded_maze: a maze_room array as a hexadecimal array based on its
 *    connections
 *  - file_name: the name of the output file for the encoded maze
 *
 * Returns:
 *  - 1 if an error occurs, 0 otherwise
 */
int write_encoded_maze_to_file(int num_rows, int num_cols,
                               int encoded_maze[num_rows][num_cols],
                               char *file_name) {
    int err = 0;

    // open file (create it if necessary)
    FILE *f = fopen(file_name, "w+");
    if (f == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    // write each room's hex value into file
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            int encoded_room = encoded_maze[i][j];
            err = fprintf(f, "%x", encoded_room);
            if (err < 0) {
                fprintf(stderr, "Writing to file failed: %i\n", err);
                return 1;
            }
        }
        // add a newline between rows
        err = fprintf(f, "\n");
        if (err < 0) {
            fprintf(stderr, "Writing to file failed: %i\n", err);
            return 1;
        }
    }
    // close file
    int close = fclose(f);
    if (close == EOF) {
        fprintf(stderr, "Could not close file.\n");
        return 1;
    }
    return 0;
}

/*
 * Main function
 *
 * Parameters:
 *  - argc: the number of command line arguments - for this function 4
 *  - **argv: a pointer to the first element in the command line
 *            arguments array - for this function:
 *            ["generator", <output file>, <number of rows>, <number of
 *columns>]
 *
 * Returns:
 *  - 0 if program exits correctly, 1 if there is an error
 */

int main(int argc, char **argv) {
    char *file_name;
    int num_rows;
    int num_cols;

    if (argc != 4) {
        printf("Incorrect number of arguments.\n");
        printf(
            "./generator <output file> <number of rows> <number of columns>\n");
        return 1;
    } else {
        file_name = argv[1];
        num_rows = atoi(argv[2]);
        num_cols = atoi(argv[3]);
    }
    if(num_rows <= 0 || num_cols <= 0){
        fprintf(stderr, "invalid row or column arguments");
            return 1;
    }
    struct maze_room currentMaze[num_rows][num_cols];
    initialize_maze(num_rows, num_cols, currentMaze); 
    drunken_walk(0, 0, num_rows, num_cols, currentMaze); 
    int resultMaze [num_rows][num_cols];
    encode_maze(num_rows, num_cols, currentMaze, resultMaze);
    write_encoded_maze_to_file(num_rows, num_cols, resultMaze, file_name);  
    // TODO: implement this function
}
