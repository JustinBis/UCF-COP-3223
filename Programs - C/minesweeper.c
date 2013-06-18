/* ****************** */
/* P8 - Minesweeper   */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 11/2/2012          */
/* ****************** */

#include <stdio.h>

#define SIZE 8
#define BOMB 9

int main(void){
    // Initilize Variables
    int boardnumber, i, j, numboards, numbombs, bombRow, bombCol;

    // Create the minesweeper array
    int board[SIZE][SIZE];

    // Open File
    FILE *ifp;
    ifp = fopen("mine.txt", "r");

    // Read the number of boards
    fscanf(ifp, "%d", &numboards);

    // Outer loop for each board
    for (boardnumber=0; boardnumber<numboards; boardnumber++){
        // Print header
        printf("Board #%d:\n", boardnumber+1);

        // Set entire board to 0s
        for(i=0; i<SIZE; i++)
            for(j=0; j<SIZE; j++)
                board[i][j] = 0;

        // Read in the number of bombs for this particular board
        fscanf(ifp, "%d", &numbombs);

        // For each bomb, read in the location and store it in the array.
        for (i=0; i<numbombs; i++){
            fscanf(ifp, "%d %d", &bombRow, &bombCol);
            board[bombRow][bombCol] = BOMB;

            // Also, increment the surrounding 8 squares by 1
            // Only increment the squre if it is inside of the bounds of the array and the squre isn't a bomb

            // Top Left
            if (bombRow-1 >= 0 && bombCol-1 >= 0 && board[bombRow-1][bombCol-1] != BOMB)
                board[bombRow-1][bombCol-1]++;

            // Top
            if (bombRow-1 >= 0 && board[bombRow-1][bombCol] != BOMB)
                board[bombRow-1][bombCol]++;

            // Top Right
            if (bombRow-1 >= 0 && bombCol+1 < SIZE && board[bombRow-1][bombCol+1] != BOMB)
                board[bombRow-1][bombCol+1]++;

            // Left
            if (bombCol-1 >= 0 && board[bombRow][bombCol-1] != BOMB)
                board[bombRow][bombCol-1]++;

            // Right
            if (bombCol+1 < SIZE && board[bombRow][bombCol+1] != BOMB)
                board[bombRow][bombCol+1]++;

            // Bottom Left
            if (bombRow+1 < SIZE && bombCol-1 >= 0 && board[bombRow+1][bombCol-1] != BOMB)
                board[bombRow+1][bombCol-1]++;

            // Bottom
            if (bombRow+1 < SIZE && board[bombRow+1][bombCol] != BOMB)
                board[bombRow+1][bombCol]++;

            // Bottom Right
            if (bombRow+1 < SIZE && bombCol+1 < SIZE && board[bombRow+1][bombCol+1] != BOMB)
                board[bombRow+1][bombCol+1]++;


        }

        // Print the output by looping through each value of the board
        for (i=0; i<SIZE; i++){
            for (j=0; j<SIZE; j++){
                if (board[i][j]==BOMB)
                    printf("* ");
                else
                    printf("%d ", board[i][j]);
            }
            printf("\n");
        }


        // Seperate each board with a blank line
        printf("\n");
    }

    // Since we are done with the file, close it
    fclose(ifp);

    // Program Completed, so return 0.
    return 0;
}
