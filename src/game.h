#ifndef _GAME_H_
#define _GAME_H_

typedef struct TheBoard {
    int tiles[9];
    int playerTiles[9];
    char horizontalOperators[6];
    char verticalOperators[6];
    int currentX;
    int currentY;
} Board;

void initBoard(Board *board);
int resultForBoardRow(Board *board, int row);
int resultForBoardCol(Board *board, int col);

#endif //_GAME_H_
