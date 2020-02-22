#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

// https://stackoverflow.com/questions/6127503/shuffle-array-in-c
/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffleInt(int *array, size_t n)
{
    int i;

    for (i = 0; i < n - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void shuffleChar(char *array, size_t n)
{
    int i;

    for (i = 0; i < n - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        char t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void setupBoard(Board *board)
{
    int i;

    for (i=0; i<9; i++)
    {
        board->tiles[i] = i + 1;
    }
    strcpy(board->horizontalOperators, "++++--");
    strcpy(board->verticalOperators, "++++--");
    _randomize();
    shuffleInt(board->tiles, 9);
    shuffleChar(board->horizontalOperators, 6);
    shuffleChar(board->verticalOperators, 6);
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
