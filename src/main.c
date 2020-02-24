#include "game.h"
#include "screen.h"
#include <conio.h>
#include <ctype.h>
#include <stdio.h>

static Board board;

int main()
{
    char c;
    int x, y;
    int currentX = 0, currentY = 0;

    initScreen();
    initBoard(&board);
    drawBoard(&board);

    while (c != 'q')
    {
        c = cgetc();
        switch (c)
        {
        case 'a':
            if (board.currentX > 0)
                board.currentX--;
            break;
        case 's':
            if (board.currentY < 2)
                board.currentY++;
            break;
        case 'd':
            if (board.currentX < 2)
                board.currentX++;
            break;
        case 'w':
            if (board.currentY > 0)
                board.currentY--;
            break;
        case 'h':
            textcolor(1);
            for (x = 0; x < 3; x++)
            {
                for (y = 0; y < 3; y++)
                {
                    gotoxy(x, y);
                    printf("%d", board.tiles[3*y+x]);
                }
            }
            break;
        default:
            break;
        }

        if (isdigit(c))
        {
            int i;
            int value = c - 48;
            int index = 0;

            if (value > 0)
            {
                for (i = 0; i < 10; i++)
                {
                    if (board.playerTiles[i] == value)
                    {
                        board.playerTiles[i] = 0;
                    }
                }

                index = 3 * board.currentY + board.currentX;
                board.playerTiles[index] = value;
            }
        }

        drawBoard(&board);
    }
    return 0;
}
