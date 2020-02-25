#include "screen.h"
#include "game.h"
#include <conio.h>
#include <stdio.h>

int main()
{
    Board board;

    initScreen();
    showHelp(1);
    clrscr();
    gameLoop(&board);

    return 0;
}
