// Author: Tori Anonuevo
// Purpose: User can play reversi against the program in the terminal. The program applies common reversi strategies to make logical plays.

#include <stdio.h>
#include <string.h>
#include <math.h>

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

int convertToInt(char letter) {
    int number = letter - 'a';
    return number;
}

char convertToLetter(int number) {
    char letter = number + 'a';
    return letter;
}

char getOppositeColour(char colour) {
    if (colour == 'W') {
        return 'B';
    }
    else if (colour == 'B') {
        return 'W';
    }
}

bool possibleMoves(char possibleBoard[26][26], char colour, int dimension, char board[][26]) {
    char opposite = getOppositeColour(colour);
    bool movesAvailable = false;

    for (int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            possibleBoard[i][j] = 'U';
        }
    }

    for (int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            if (board[i][j] == opposite) {
                if(board[i - 1][j - 1] == 'U' && checkLegalInDirection(board, dimension, i - 1, j - 1, colour, 1, 1)) {
                    possibleBoard[i - 1][j - 1] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i - 1][j] == 'U' && checkLegalInDirection(board, dimension, i - 1, j, colour, 1, 0)) {
                    possibleBoard[i - 1][j] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i - 1][j + 1] == 'U' && checkLegalInDirection(board, dimension, i - 1, j + 1, colour, 1, -1)) {
                    possibleBoard[i - 1][j + 1] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i][j - 1] == 'U' && checkLegalInDirection(board, dimension, i, j - 1, colour, 0, 1)) {
                    possibleBoard[i][j - 1] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i][j + 1] == 'U' && checkLegalInDirection(board, dimension, i, j + 1, colour, 0, -1)) {
                    possibleBoard[i][j + 1] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i + 1][j - 1] == 'U' && checkLegalInDirection(board, dimension, i + 1, j - 1, colour, -1, 1)) {
                    possibleBoard[i + 1][j - 1] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i + 1][j] == 'U' && checkLegalInDirection(board, dimension, i + 1, j, colour, -1, 0)) {
                    possibleBoard[i + 1][j] = 'P';
                    movesAvailable = true;                    
                }
                if(board[i + 1][j + 1] == 'U' && checkLegalInDirection(board, dimension, i + 1, j + 1, colour, -1, -1)) {
                    possibleBoard[i + 1][j + 1] = 'P';
                    movesAvailable = true;                    
                }
            }
        }
    }
    return movesAvailable;
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

void changeIntermediateTiles(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol) {
    int multiplier = 1;
    char opposite = getOppositeColour(colour);
    while (board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == opposite) {
        board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] = colour;
        multiplier++;
    }
    return;
}

void placeTile(char colour, int row, int col, int n, char board[][26]) {
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

bool userMove(char board[][26], char possibleBoard[][26], int dimension, char humanColour) {
    char move[3];
    printf("Enter move for colour %c (RowCol): ", humanColour);
    scanf(" %s", move);
    int row = convertToInt(move[0]);
    int col = convertToInt(move[1]);
    if (positionInBounds(dimension, row, col) == false || possibleBoard[row][col] != 'P') {
        printf("Invalid move.\n");
        return false;
    }
    else placeTile(humanColour, row, col, dimension, board);
    return true;
}

int countIntermediateTiles(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol) {
    int multiplier = 1;
    char opposite = getOppositeColour(colour);
    int counter = 0;
    while (board[row + (multiplier*deltaRow)][col + (multiplier*deltaCol)] == opposite) {
        counter++;
        multiplier++;
    }
    return counter;
}

int calculateTotalTurnedTiles(char board[][26], int row, int col, char colour, int n) {
    int sum = 0;
    if (checkLegalInDirection(board, n, row, col, colour, -1, -1)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, -1, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, 0)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, -1, 0);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, 1)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, -1, 1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, -1)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, 0, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, 1)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, 0, 1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, -1)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, 1, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 0)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, 1, 0);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 1)) {
        sum = sum + countIntermediateTiles(board, row, col, colour, 1, 1);
    }
    // printf("turned = %d\n", sum);
    return sum;
}

int possibleOpponentScore(char board[][26], int row, int col, int dimension, char colour, char possibleOpponentBoard[][26]) {
    // Copy board into dummy board
    char dummy[26][26]; 
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            dummy[i][j] = board[i][j];
        }
    }
    // Put piece on dummy
    placeTile(colour, row, col, dimension, dummy);
    // Run possible moves for human on dummy board and possible board
    char opponentColour = getOppositeColour(colour);
    bool isPossibleMove = possibleMoves(possibleOpponentBoard, opponentColour, dimension, dummy);
    if (isPossibleMove == true) {
        // Calculate posisble scores for human around the piece that was just placed
        int currentScore = 0, bestScore = 0;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (possibleOpponentBoard[row + i][col + j] == 'P') {
                    currentScore = calculateTotalTurnedTiles(dummy, row + i, col + j, opponentColour, dimension);
                    if (currentScore > bestScore) {
                        bestScore = currentScore;
                    }
                }
            }
        }
        return bestScore;
    }
    else {
        return 0;
    }
}

int positionScore(char board[][26], int row, int col, int end, char colour) {
    char opponentColour = getOppositeColour(colour);
    // Top Row
    if (row == 0) {
        // Corner
        if (col == 0 || col == end) {
            return 100;
        }
        // Surrounding Square
        if (col == 1 || col == end - 1) {
            return -5;
        }
        // Edges
        if ((board[0][0] != 'U' && board[0][end] != 'U') || board[0][0] == colour || board[0][end] == colour) {
            return 4;
        }
        else if (board[0][0] == 'U' && board[0][end] == 'U') {
            return 1;
        }
        else if (board[0][0] == opponentColour || board[0][end] == opponentColour) {
            return -5;
        }
    }
    // Bottom Row
    else if (row == end) {
        // Corner
        if (col == 0 || col == end) {
            return 100;
        }
        // Surrounding Square
        if (col == 1 || col == end - 1) {
            return -5;
        }
        // Edges
        if ((board[end][0] != 'U' && board[end][end] != 'U') || board[end][0] == colour || board[end][end] == colour) {
            return 4;
        }
        else if (board[end][0] == 'U' && board[end][end] == 'U') {
            return 1;
        }
        else if (board[end][0] == opponentColour || board[end][end] == opponentColour) {
            return -5;
        }
    }

    // Side Edges
    if ((col == 0 || col == end) && row != 0 && row != end) {
        if (row == 1 || row == end - 1) {
            return -5;
        }

        if (col == 0) {
            if (board[0][0] == colour || board[end][0] == colour || (board[0][0] != 'U' && board[end][0] != 'U')) {
                return 4;
            }
            else if (board[end][0] == opponentColour || board[0][0] == opponentColour) {
                return -5;
            }
            else {
                return 1;
            }
        }
        else if (col == end) {
            if (board[0][end] == colour || board[end][end] == colour || (board[0][end] != 'U' && board[end][end] != 'U')) {
                return 4;
            }
            else if (board[end][end] == opponentColour || board[0][end] == opponentColour) {
                return -5;
            }
            else {
                return 1;
            }
        }
    }

    // Middle Area
    if ((row == 1 && col == 1) || (row == 1 && col == end - 1) || (row == end - 1 && col == 1) || (row == end - 1 && col == end - 1)) {
        return -5;
    }
    else return (end - 2) - abs((end/2) - row) - abs((end/2) - col);
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {
    char possibleBoard[26][26];
    bool foundPossibleMoves = possibleMoves(possibleBoard, turn, n, board);
    char possibleOpponentBoard[26][26];
    bool foundPossibleOpponentMoves = possibleMoves(possibleBoard, turn, n, board);

    int bestScore = -1000;
    int currentScore = 0;
    // printBoard(possibleBoard, dimension);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (possibleBoard[i][j] == 'P') {
                currentScore = calculateTotalTurnedTiles(board, i, j, turn, n);
                currentScore = currentScore + positionScore(board, i, j, n - 1, turn) - possibleOpponentScore(board, i, j, n, turn, possibleOpponentBoard);
                // printf("Current Score: %d at %d %d", currentScore, i, j);
                if (bestScore < currentScore) {
                    bestScore = currentScore;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
    return 0;
}

int countColour(char colour, char board[][26], int dimension) {
    int counter = 0;
    for (int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            if (board[i][j] == colour) counter++;
        }
    }
    return counter;
}
