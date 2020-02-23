#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "utils-random.h"

void initBoard(Board *board)
{
    int i;

    for (i=0; i<9; i++)
    {
        board->tiles[i] = i + 1;
        board->playerTiles[i] = 0;
    }
    strcpy(board->horizontalOperators, "++++--");
    strcpy(board->verticalOperators, "++++--");

    _randomize();
    shuffleIntArray(board->tiles, 9);
    shuffleCharArray(board->horizontalOperators, 6);
    shuffleCharArray(board->verticalOperators, 6);
}

int calculate(int a, int b, char op) {
    switch(op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        default:
            return 0;
    }
}

int resultForBoardRow(Board *board, int row)
{
    int a, b, c;
    char op1, op2;

    a = board->tiles[3 * row + 0];
    op1 = board->horizontalOperators[2 * row + 0];
    b = board->tiles[3 * row + 1];
    op2 = board->horizontalOperators[2 * row + 1];
    c = board->tiles[3 * row + 2];

    return calculate(calculate(a, b, op1), c, op2);
}

int resultForBoardCol(Board *board, int col)
{
    int a, b, c;
    char op1, op2;

    a = board->tiles[col + 0];
    op1 = board->verticalOperators[2 * col + 0];
    b = board->tiles[col + 3];
    op2 = board->verticalOperators[2 * col + 1];
    c = board->tiles[col + 6];

    return calculate(calculate(a, b, op1), c, op2);
}
