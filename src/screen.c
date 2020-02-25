#include "screen.h"
#include "game.h"
#include <conio.h>
#include <stdio.h>

int colorForResult(ResultType result) {
    switch (result)
    {
    case Inconclusive:
        return 15;
    case Right:
        return 5;
    case Wrong:
        return 10;
    default:
        return 0;
    }
}

int colorForRow(Board *board, int row)
{
    ResultType result = resultTypeForRow(board, row);
    return colorForResult(result);
}

int colorForCol(Board *board, int col)
{
    ResultType result = resultTypeForCol(board, col);
    return colorForResult(result);
}

void initScreen()
{
    bordercolor(0);
    bgcolor(0);
    textcolor(1);
    clrscr();
    cursor(1);
}

void drawTiles(Board *board) {
    int x, y, tile;

    textcolor(1);
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            tile = board->playerTiles[3 * y + x];
            gotoxy(board->startX + 4 * x, board->startY + 4 * y);
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
}

void drawOperators(Board *board)
{
    int x, y;
    textcolor(11);

    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < 3; y++)
        {
            gotoxy(board->startX + 4 * x + 2, board->startY + 4 * y);
            printf("%c", board->horizontalOperators[2 * y + x]);
        }
    }

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 2; y++)
        {
            gotoxy(board->startX + 4 * x, board->startY + 4 * y + 2);
            printf("%c", board->verticalOperators[2 * x + y]);
        }
    }
}

void drawResults(Board *board)
{
    int x;

    for (x = 0; x < 3; x++)
    {
        textcolor(11);
        gotoxy(board->startX + 10, board->startY + 4 * x);
        printf("=");
        gotoxy(board->startX + 12, board->startY + 4 * x);
        textcolor(colorForRow(board, x));
        printf("%d", resultForBoardRow(board, x));

        textcolor(11);
        gotoxy(board->startX + 4 * x, board->startY + 10);
        printf("=");
        gotoxy(board->startX + 4 * x, board->startY + 12);
        textcolor(colorForCol(board, x));
        printf("%d", resultForBoardCol(board, x));
    }
}
void drawAvailableTiles(Board *board)
{
    int x, y;
    int tileUsed;

    textcolor(14);

    for (x = 1; x < 10; x++)
    {
        tileUsed = 0;

        for (y = 0; y < 10; y++)
        {
            if (tileUsed == 0 && board->playerTiles[y] == x)
            {
                tileUsed = 1;
            }
        }

        gotoxy(board->startX + 2 * x - 4, board->startY + 16);
        if (tileUsed)
        {
            printf(" ");
        }
        else
        {
            printf("%d", x);
        }
    }
}

void setCursorOnPlayerPosition(Board *board)
{
    textcolor(1);
    gotoxy(board->startX + 4 * board->currentX, board->startY + 4 * board->currentY);
}

void drawBoard(Board *board)
{   
    drawTiles(board);
    drawOperators(board);
    drawResults(board);
    drawAvailableTiles(board);
}
