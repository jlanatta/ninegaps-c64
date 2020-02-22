#ifndef _GAME_H_
#define _GAME_H_

typedef struct TheBoard {
    char tiles[9];
    char horizontalOperators[6];
    char verticalOperators[6];
} Board;

void setupBoard(Board *board);

#endif //_GAME_H_
