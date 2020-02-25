#include "game.h"

#ifndef _SCREEN_H_
#define _SCREEN_H_

void initScreen(void);
void drawTiles(Board *board);
void drawOperators(Board *board);
void drawResults(Board *board);
void drawAvailableTiles(Board *board);
void setCursorOnPlayerPosition(Board *board);
void drawBoard(Board *board);
void showHelp(int firstTime);

#endif //_SCREEN_H_
