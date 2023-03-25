//
// Author: Tori Anonuevo
//

// #include "reversi.h"
#include <stdio.h>
#include <string.h>

void printBoard(char board[][26], int n) {
    char gridLetter ='a';
    printf("  ");
    for (int k = 0; k < n; k++) {
        printf("%c", gridLetter + k);
    }
    printf("\n");
    gridLetter = 'a';
    for (int i = 0; i < n; i++) {
        printf("%c ", gridLetter);
        gridLetter++;
        for (int j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return;
}

bool positionInBounds(int n, int row, int col) {
    return (row < n && col < n && row >= 0 && col >= 0);
}

// Function that converts the grid letters to their corresponding matrix indices
int convertToInt(char letter) {
    int number = letter - 'a';
    return number;
}

// Function that converts the matrix indices to their corresponding grid letters
char convertToLetter(int number) {
    char letter = number + 'a';
    return letter;
}

// function that returns the opposite colour 
char getOppositeColour(char colour) {
    if (colour == 'W') {
        return 'B';
    }
    else if (colour == 'B') {
        return 'W';
    }
}

// Function that determines the possible moves for a given colour
void possibleMoves(char board[][26], char colour, int dimension) {
    char opposite = getOppositeColour(colour);

    printf("Available moves for %c:\n", colour);

    for (int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            if (board[i][j] == opposite) {
                if(board[i - 1][j - 1] == 'U' && checkLegalInDirection(board, dimension, i - 1, j - 1, colour, 1, 1)) {
                    board[i - 1][j - 1] = 'P';                    
                }
                if(board[i - 1][j] == 'U' && checkLegalInDirection(board, dimension, i - 1, j, colour, 1, 0)) {
                    board[i - 1][j] = 'P';                    
                }
                if(board[i - 1][j + 1] == 'U' && checkLegalInDirection(board, dimension, i - 1, j + 1, colour, 1, -1)) {
                    board[i - 1][j + 1] = 'P';                    
                }
                if(board[i][j - 1] == 'U' && checkLegalInDirection(board, dimension, i, j - 1, colour, 0, 1)) {
                    board[i][j - 1] = 'P';                    
                }
                if(board[i][j + 1] == 'U' && checkLegalInDirection(board, dimension, i, j + 1, colour, 0, -1)) {
                    board[i][j + 1] = 'P';                    
                }
                if(board[i + 1][j - 1] == 'U' && checkLegalInDirection(board, dimension, i + 1, j - 1, colour, -1, 1)) {
                    board[i + 1][j - 1] = 'P';                    
                }
                if(board[i + 1][j] == 'U' && checkLegalInDirection(board, dimension, i + 1, j, colour, -1, 0)) {
                    board[i + 1][j] = 'P';                    
                }
                if(board[i + 1][j + 1] == 'U' && checkLegalInDirection(board, dimension, i + 1, j + 1, colour, -1, -1)) {
                    board[i + 1][j + 1] = 'P';                    
                }
            }
        }
    }
    
    for (int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            if (board[i][j] == 'P') {
                printf("%c%c\n", convertToLetter(i), convertToLetter(j));
            }
        }
    }

    return;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    if (positionInBounds(n, row, col) == false) {
        return false;
    }

    char opposite = getOppositeColour(colour);
    if (board[row + deltaRow][col + deltaCol] != opposite) return false;
    
    int multiplier = 2;
    while (positionInBounds(n, multiplier*deltaRow + row, multiplier*deltaCol + col)) {
        if (board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == colour) {
            return true;
        }
        if (board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == opposite) {
            multiplier++;
        }
        else if (board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == 'U' || board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == 'P') {
            return false;
        }
    }
    return false;
}

// Function that changes the tiles between a placed tile and existing tile of the same colour
void changeIntermediateTiles(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol) {
    int multiplier = 1;
    char opposite = getOppositeColour(colour);
    while (board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == opposite) {
        board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] = colour;
        multiplier++;
    }
    return;
}

// Function that makes the inputted move if vaild
void placeTile(char colour, int row, int col, int n, char possibleMoves[][26], char board[][26]) {
    if (positionInBounds(n, row, col) == false || possibleMoves[row][col] != 'P') {
        printf("Invalid move.\n");
        return;
    }

    printf("Valid move.\n");
    board[row][col] = colour;

    if (checkLegalInDirection(board, n, row, col, colour, -1, -1)) {
        changeIntermediateTiles(board, row, col, colour, -1, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, 0)) {
        changeIntermediateTiles(board, row, col, colour, -1, 0);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, 1)) {
        changeIntermediateTiles(board, row, col, colour, -1, 1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, -1)) {
        changeIntermediateTiles(board, row, col, colour, 0, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, 1)) {
        changeIntermediateTiles(board, row, col, colour, 0, 1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, -1)) {
        changeIntermediateTiles(board, row, col, colour, 1, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 0)) {
        changeIntermediateTiles(board, row, col, colour, 1, 0);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 1)) {
        changeIntermediateTiles(board, row, col, colour, 1, 1);
    }

    return;
    
}

int main(void) {
    int dimension = 0;
    printf("Enter the board dimension: ");
    scanf("%d", &dimension);

    // Part 1: Initialize Board
    char board[26][26];
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            board[i][j] = 'U';
        }
    }
    board[dimension / 2 - 1][dimension / 2 - 1] = 'W';
    board[dimension / 2 - 1][dimension / 2] = 'B';
    board[dimension / 2][dimension / 2] = 'W';
    board[dimension / 2][dimension / 2 - 1] = 'B';
    printBoard(board, dimension);

    // Part 2: Set Configuration
    char configuration[4] = {'U', 'a', 'a', '\0'};
    printf("Enter board configuration:\n");
    scanf(" %s", configuration);
    while (strcmp(configuration, "!!!") != 0) {
        board[convertToInt(configuration[1])][convertToInt(configuration[2])] = configuration[0];
        scanf(" %s", configuration);
    }
    printBoard(board, dimension);

    // Part 3: Possible Moves
    char possibleWhite[26][26];
    char possibleBlack[26][26];
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            possibleWhite[i][j] = board[i][j];
            possibleBlack[i][j] = board[i][j];
        }
    }
    possibleMoves(possibleWhite, 'W', dimension);
    possibleMoves(possibleBlack, 'B', dimension);

    // Part 4: User-Inputted Move 
    char move[4];
    printf("Enter a move:\n");
    scanf(" %s", move);
    int row = convertToInt(move[1]);
    int col = convertToInt(move[2]);
    if (move[0] == 'W') {
        placeTile(move[0], row, col, dimension, possibleWhite, board);
    }
    else if (move[0] == 'B') {
        placeTile(move[0], row, col, dimension, possibleBlack, board);
    }

    // Part 5: Print Final Board
    printBoard(board, dimension);

    return 0;
}
