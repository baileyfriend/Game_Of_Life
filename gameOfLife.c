/*
    Bailey Freund
    CIS 343 02 
    Professor Woodring
    2/12/18
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utilities.h"

int create_board(char **, int, int);

int populate_board(char **, char *, int, int);

int free_board(char **, int);

int print_board(char ** , int , int );

int continue_board(char ** , int , int );

char ALIVE = 'A';
char DEAD = 'D';

int main(int argc,char* argv[]) { 
    printf("BEGIN \n");
    char *row = argv[1];
    char *col = argv[2];
    char *ptr;

    int num_rows = strtol(row, &ptr, 10);
    int num_cols = strtol(col, &ptr, 10);

    printf("num rows: %i   num cols: %i \n", num_rows, num_cols);
    // Create board
    printf("create board \n");
    char **board = (char **)malloc(num_rows*sizeof(char*));
    create_board(board, num_rows, num_cols);
    printf("board created \n");
    // populate initial board
    int r = 0;
    int c = 0;
    int rando = 0;
    for ( r = 0; r < num_rows; r++){
        for ( c = 0; c < num_cols; c++){
            rando = rand() % (1 + 1 - 0) + 0;
            if(rando){
                board[r][c] = DEAD;
            } else {
                board[r][c] = ALIVE;
            }
            
            printf("%c ", board[r][c]);
        }
        printf("\n");
    }
        

    while(1){
        printf("What would you like to do (save, load, continue, or exit)?\n");
        char input[10];
        fgets(input, 10, stdin); // https://stackoverflow.com/questions/22065675/get-text-from-user-input-using-c
        //char* token = strtok(input, " ");con

        printf("You entered %s\n", input);

        if( strcmp(input, "save\n\0") == 0){
            printf("Saving file\n"); 
            char* file = "some_file.txt";
            write_file( file, board, num_rows, num_cols );

        } else if( strcmp(input, "load\n\0") == 0 ){
            char *filename = "some_file.txt\0";
            //printf("What file (must be in this directory)? \n"); // @TODO implement load function
            //fgets(filename, 50, stdin);
            //char **data = 
            read_file(filename, board);
            print_board(board, num_rows, num_cols);
            

            
        } else if( strcmp(input, "continue\n\0") == 0 ){
            printf("Continuing to next generation\n"); //@TODO implement continue function - must evaluate rules
            continue_board(board, num_rows, num_cols);
        } else if( strcmp(input, "exit\n\0") == 0 ){
            printf("EXITING PROGRAM");
            free_board(board, num_rows);
            return 0;
        } else
            printf("Invalid command. Please enter save, load, or continue. \n");
    }

    return 0;
}

/*
    Creates a board with a specific number of rows and columns
*/
int create_board(char **board, int num_rows, int num_cols){
    for (int i=0; i< num_rows; i++){
        printf("Creating row %i \n", i );
        board[i] = (char *)malloc(num_cols*sizeof(char));
        for( int j=0; j<num_cols; j++){
            board[i][j] = '0';
        }
    }

    print_board(board, num_rows, num_cols);
    return 0;
}


/*
    Populates the board with the data passed. Used in conjunction with read_file
    @param board the board to populate
    @param data the data to populate the board with
    @param num_rows the number of rows in the board
    @param num_cols the number of cols in the board
*/
int populate_board(char **board, char *data, int num_rows, int num_cols){
    int r = 0;
    int c = 0;
    int i = 0;
    for ( r = 0; r < num_rows; r++){
        for ( c = 0; c < num_cols; c++){
            board[r][c] = data[i];
            printf("%c ", board[r][c]);
            i++;
        }
    }
    return 0;
}

/*
    Loops through board and frees each sub-array, then frees the array itself
    @param board the board to be freed. Must be a 2d array.
*/
int free_board(char **board, int num_rows){
    for (int i=0; i < num_rows; i++){
        free(board[i]);
    }
    free(board);
    return 0;
}

int print_board(char **board, int num_rows, int num_cols) {
    int r = 0;
    int c = 0;
    printf("BOARD: \n");
    for ( r = 0; r < num_rows; r++){
        for ( c = 0; c < num_cols; c++){
            printf("%c ", board[r][c]);
        }
        printf("\n");
    }
    return 0;
}

int continue_board(char **board, int num_rows, int num_cols){
    int r = 0;
    int c = 0;
    int count = 0;
    printf("BOARD: \n");
    for ( r = 0; r < num_rows; r++){
        printf("outer loop \n");
        for ( c = 0; c < num_cols; c++){
            printf("inner loop \n");
            count = 0;
            if( r - 1 >= 0 ) { // check if there is a row above current
                printf("1st if \n");
                if( board[r-1][c] != DEAD ) count ++; // check above
                if( c - 1 >= 0 ) { // check if there's a column to the left
                    if( board[r-1][c-1] != DEAD ) count ++; // check above left
                    if( board[r][c-1] != DEAD ) count ++; // check left
                }
            }
            
            if( r + 1 < num_rows ) { // check if there is a row above current
                printf("2nd if \n");
                if( board[r+1][c] != DEAD ) count ++; // check below
                if( c + 1 < num_cols ) { // check if there's a column to the right
                    printf("2.1 if \n");
                    if( board[r+1][c+1] != DEAD ) count ++; // check below right
                    if( board[r][c+1] != DEAD ) count ++; // check below
                    printf("after 2.1 eval \n");
                }
            }

            if(count < 2 || count > 3) board[r][c] = DEAD;
            if(board[r][c] == DEAD ){ // cell is currently dead
                if(count == 3) board[r][c] = ALIVE;
            }
        }
    }

    print_board(board, num_rows,num_cols);
    return 0;

}
