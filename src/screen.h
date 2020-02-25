#include "game.h"

#ifndef _SCREEN_H_
#define _SCREEN_H_

typedef enum resultType
{
    Inconclusive,
    Right,
    Wrong
} ResultType;

void initScreen(void);
void drawBoard(Board *board);

ResultType resultTypeForRow(Board *board, int row);
ResultType resultTypeForCol(Board *board, int col);

int colorForRow(Board *board, int row);
int colorForCol(Board *board, int col);
int colorForResult(ResultType result);


#endif //_SCREEN_H_
