#include "screen.h"
#include "game.h"
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

    for (x=0; x<3; x++) {
        gotoxy(startX + 10, startY + 4 * x);
        printf("=");
        gotoxy(startX + 12, startY + 4 * x);
        printf("%d", resultForBoardRow(board, x));
        gotoxy(startX + 4 * x, startY + 10);
        printf("=");
        gotoxy(startX + 4 * x, startY + 12);
        printf("%d", resultForBoardCol(board, x));
    }

// int resultForBoardRow(Board *board, int row);
// int resultForBoardCol(Board *board, int col);

    gotoxy(0, 0);
}