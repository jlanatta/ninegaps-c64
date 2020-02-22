#include "screen.h"
#include <conio.h>
#include <stdio.h>

void setupScreen() {
    bordercolor(0);
    bgcolor(0);
    textcolor(1);
    clrscr();
}

void drawBoard(Board *board) {
    int x, y;
    int startX = 4, startY = 4;

    for (x=0; x<3; x++) {
        for (y=0; y<3; y++) {
            if (x % 2 == 0 && y % 2 == 0) {
                textcolor(5);
            } else {
                textcolor(2);
            }
            gotoxy(startX + 4 * x, startY + 4 * y);
            printf("%c", board->tiles[3 * y + x]);
        }
    }

    textcolor(1);

    for (x=0; x<2; x++) {
        for (y=0; y<3; y++) {
            gotoxy(startX + 4 * x + 2, startY + 4 * y);
            printf("%c", board->horizontalOperators[2 * y + x]);
        }
    }
    for (x=0; x<3; x++) {
        for (y=0; y<2; y++) {
            gotoxy(startX + 4 * x, startY + 4 * y + 2);
            printf("%c", board->verticalOperators[2 * x + y]);
        }
    }
    gotoxy(0, 0);
}