#include "screen.h"
#include "game.h"
#include <conio.h>
#include <stdio.h>

void initScreen()
{
    bordercolor(0);
    bgcolor(0);
    textcolor(1);
    clrscr();
    cursor(1);
}

void drawBoard(Board *board)
{
    int x, y, tile;
    int startX = 13;
    int startY = 6;
    int tileUsed = 0;

    textcolor(1);
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            tile = board->playerTiles[3 * y + x];
            gotoxy(startX + 4 * x, startY + 4 * y);
            if (tile > 0)
            {
                printf("%d", tile);
            }
            else
            {
                printf(" ");
            }
        }
    }

    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < 3; y++)
        {
            gotoxy(startX + 4 * x + 2, startY + 4 * y);
            printf("%c", board->horizontalOperators[2 * y + x]);
        }
    }

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 2; y++)
        {
            gotoxy(startX + 4 * x, startY + 4 * y + 2);
            printf("%c", board->verticalOperators[2 * x + y]);
        }
    }

    for (x = 0; x < 3; x++)
    {
        gotoxy(startX + 10, startY + 4 * x);
        printf("=");
        gotoxy(startX + 12, startY + 4 * x);
        printf("%d", resultForBoardRow(board, x));
        gotoxy(startX + 4 * x, startY + 10);
        printf("=");
        gotoxy(startX + 4 * x, startY + 12);
        printf("%d", resultForBoardCol(board, x));
    }

    for (x = 1; x < 10; x++)
    {
        tileUsed = 0;

        for (y=0;y<10;y++) {
            if (tileUsed == 0 && board->playerTiles[y] == x) {
                tileUsed = 1;
            }
        }

        gotoxy(startX + 2*x - 4, startY + 16);
        if (tileUsed) {
            printf(" ");
        } else {
            printf("%d", x);
        }
    }

    gotoxy(startX + 4 * board->currentX, startY + 4 * board->currentY);
}