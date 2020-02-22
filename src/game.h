#ifndef _GAME_H_
#define _GAME_H_

typedef struct TheBoard {
    int tiles[9];
    char horizontalOperators[6];
    char verticalOperators[6];
} Board;

void setupBoard(Board *board);
int resultForBoardRow(Board *board, int row);
int resultForBoardCol(Board *board, int col);

#endif //_GAME_H_
