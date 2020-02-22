#include <string.h>
#include "game.h"

void setupBoard(Board *board) {
    strcpy(board->tiles, "123456789");
    strcpy(board->horizontalOperators, "+--+++");
    strcpy(board->verticalOperators, "++--++");
}

int resultForBoardRow(Board *board, int row) {
    int a, b, c;

    a = board->tiles[3*row+0] - 48;
    b = board->tiles[3*row+1] - 48;
    c = board->tiles[3*row+2] - 48;

    return a + b + c;
}

int resultForBoardCol(Board *board, int col) {
    int a, b, c;

    a = board->tiles[col+0] - 48;
    b = board->tiles[col+3] - 48;
    c = board->tiles[col+6] - 48;

    return a + b + c;
}