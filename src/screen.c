#include "screen.h"
#include "game.h"
#include <conio.h>
#include <stdio.h>

int colorForResult(ResultType result)
{
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

void drawTitle()
{
    textcolor(1);
    gotoxy(16, 0);
    printf("NineGaps");
}

void initScreen()
{
    bordercolor(0);
    bgcolor(0);
    textcolor(1);
    clrscr();
    cursor(1);
}

void drawTiles(Board *board)
{
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

    gotoy(board->startY + 16);

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

        gotox(board->startX + 2 * x - 4);
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
    drawTitle();
    drawTiles(board);
    drawOperators(board);
    drawResults(board);
    drawAvailableTiles(board);
    textcolor(11);
    gotoxy(0, 23);
    printf(NG_VERSION);
    gotox(32);
    printf("F1: Help");
}

void showHelp(int firstTime)
{
    clrscr();
    textcolor(1);
    drawTitle();
    gotoxy(0, 3);
    printf("1. Place numbers from 1 to 9 in the\n   missing gaps.");
    gotoxy(0, 6);
    printf("2. All numbers must be used only once.");
    gotoxy(0, 8);
    printf("3. All calculations must be correct to\n   win the game.");
    gotoxy(0, 11);
    printf("4. Use WASD keys to move on the board,\n   press the number keys to place the\n   numbers.");
    gotoxy(0, 15);
    printf("5. Use inst del to remove a number.");
    gotoxy(0, 17);
    printf("6. Use F7 to reset the board.");
    gotoxy(0, 19);
    printf("6. Use F1 to show this help.");

    textcolor(11);
    if (firstTime)
    {
        gotoxy(9, 23);
        printf("Press any key to start!");
    }
    else
    {
        gotoxy(1, 23);
        printf("Press any key to return to the game.");
    }

    cgetc();
}