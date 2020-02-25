#ifndef _GAME_H_
#define _GAME_H_

typedef enum ResultType
{
    Inconclusive,
    Right,
    Wrong
} ResultType;

typedef struct Board
{
    int currentX;
    int currentY;
    int startX;
    int startY;
    int tiles[9];
    int playerTiles[9];
    int hintTiles[9];
    int hintAmount;
    char horizontalOperators[6];
    char verticalOperators[6];
    char won;
} Board;

void initBoard(Board *board);

void gameLoop(Board *board);
int resultForBoardRow(Board *board, int row);
int resultForBoardCol(Board *board, int col);
int currentResultForBoardRow(Board *board, int row);
int currentResultForBoardCol(Board *board, int col);
ResultType resultTypeForRow(Board *board, int row);
ResultType resultTypeForCol(Board *board, int col);
int isColCorrect(Board *board, int col);
int isRowCorrect(Board *board, int row);

#endif //_GAME_H_
