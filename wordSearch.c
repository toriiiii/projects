// Author: Tori Anonuevo
// Purpose: Solves a 2D word search puzzle.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printFoundLocation(int rowDir, int colDir) {
    if (rowDir == 1) {
        printf("south");
    }
    else if (rowDir == -1) {
        printf("north");
    }
    
    if (rowDir != 0 && colDir != 0) {
        printf("-");
    }

    if (colDir == 1) {
        printf("east");
    }
    else if (colDir == -1) { 
        printf("west");
    }

    printf(" direction.\n");

    return;
}

bool search1D(char word[], int wordSize, const int Size, char grid[Size][Size], int row, int col, int rowDir, int colDir) {
    for (int letter = 1; letter < wordSize; letter++) {
        if (row + rowDir >= Size || row + rowDir < 0 || col + colDir > Size || col + colDir < 0) {
            return false;
        }

        if (grid[row + rowDir][col + colDir] != word[letter]) {
            return false;
        }
        row = row + rowDir;
        col = col + colDir;
    }
    return true;
}

void search2D(char word[], int wordSize, const int Size, char grid[Size][Size]) {
    bool isWordFound = false;
    int rowDir, colDir;
    for (int row = 0; row < Size; row++) {
        for (int col = 0; col < Size; col++) {
            if (grid[row][col] == word[0]) {
                // Check South
                if (search1D(word, wordSize, Size, grid, row, col, 1, 0) == true) {
                    isWordFound = true;
                    rowDir = 1;
                    colDir = 0;
                }
                
                // Check South West to North West
                for (int i = 1; i > -2; i--) {
                    if (isWordFound == false) {
                        if (search1D(word, wordSize, Size, grid, row, col, i, -1) == true) {
                            isWordFound = true;
                            rowDir = i;
                            colDir = -1;
                        }
                    }
                }

                // Check North
                if (isWordFound == false) {
                    if (search1D(word, wordSize, Size, grid, row, col, -1, 0) == true) {
                        isWordFound = true;
                        rowDir = -1;
                        colDir = 0;
                    }
                }

                // Check North East to South East
                for (int i = -1; i < 2; i++) {
                    if (isWordFound == false) {
                        if (search1D(word, wordSize, Size, grid, row, col, i, 1) == true) {
                            isWordFound = true;
                            rowDir = i;
                            colDir = 1;
                        }
                    }
                }
            }

            if (isWordFound == true) {
                printf("Word found at row %d and column %d in the ", row, col);
                printFoundLocation(rowDir, colDir);
                return;
            }
        }
    }
    printf("Word not found.\n");
    return;
}
