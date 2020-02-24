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

typedef enum resultType {
    Inconclusive,
    Right,
    Wrong
} ResultType;

ResultType resultTypeForRow(Board *board, int row) {
    int a, b, c;
    int real, current;

    a = board->playerTiles[3 * row + 0];
    b = board->playerTiles[3 * row + 1];
    c = board->playerTiles[3 * row + 2];

    if (a > 0 && b > 0 && c > 0) {
        real = resultForBoardRow(board, row);
        current = currentResultForBoardRow(board, row);
        if (real == current) {
            return Right;
        } else {
            return Wrong;
        }
    } else {
        return Inconclusive;
    }
}

ResultType resultTypeForCol(Board *board, int col) {
    int a, b, c;
    int real, current;

    a = board->playerTiles[col + 0];
    b = board->playerTiles[col + 3];
    c = board->playerTiles[col + 6];

    if (a > 0 && b > 0 && c > 0) {
        real = resultForBoardCol(board, col);
        current = currentResultForBoardCol(board, col);
        if (real == current) {
            return Right;
        } else {
            return Wrong;
        }
    } else {
        return Inconclusive;
    }
}

int colorForRow(Board *board, int row) {
    switch (resultTypeForRow(board, row))
    {
    case Inconclusive:
        return 1;
    case Right:
        return 5;
    case Wrong:
        return 10;
    default:
        return 0;
    }
}

int colorForCol(Board *board, int col) {
    switch (resultTypeForCol(board, col))
    {
    case Inconclusive:
        return 1;
    case Right:
        return 5;
    case Wrong:
        return 10;
    default:
        return 0;
    }
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

    textcolor(11);

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
        textcolor(11);
        gotoxy(startX + 10, startY + 4 * x);
        printf("=");
        gotoxy(startX + 12, startY + 4 * x);
        textcolor(colorForRow(board, x));
        printf("%d", resultForBoardRow(board, x));
        
        textcolor(11);
        gotoxy(startX + 4 * x, startY + 10);
        printf("=");
        gotoxy(startX + 4 * x, startY + 12);
        textcolor(colorForCol(board, x));
        printf("%d", resultForBoardCol(board, x));
    }

    textcolor(11);

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

