#include <string.h>
#include "game.h"

void setupBoard(Board *board) {
    strcpy(board->tiles, "123456789");
    strcpy(board->horizontalOperators, "+--+++");
    strcpy(board->verticalOperators, "++--++");
}