#include <stdio.h>
// Author: Tori Anonuevo
// Purpose: Solves a sudoko puzzle.

#include <stdbool.h>

int findMissingNumber(int row, int col, const int Size, int sudoko[Size][Size]);

void fillSudoko(const int Size, int sudoko [Size][Size]){
    int missingNumber = 0;
    for (int row = 0; row < Size; row++) {
        for (int col = 0; col < Size; col++) {
            if (sudoko[row][col] == 0) {
                missingNumber = findMissingNumber(row, col, Size, sudoko);
                sudoko[row][col] = missingNumber;
            }
        }
    }
    return;
}

// Function that determines the missing value from a row and column combination
int findMissingNumber(int row, int col, const int Size, int sudoko[Size][Size]) {
    int foundNumbers[4] = {0};
    for (int i = 0; i < Size; i++) {
        if(sudoko[row][i] != 0) {
            foundNumbers[sudoko[row][i]-1] = 1; 
        }
        if(sudoko[i][col] != 0) {
            foundNumbers[sudoko[i][col]-1] = 1; 
        }
    }

    for (int j = 0; j < Size; j++) {
        if (foundNumbers[j] == 0) {
            return j + 1;
        }
    }
}
