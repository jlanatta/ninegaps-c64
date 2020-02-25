#include "screen.h"
#include "game.h"
#include <conio.h>
#include <stdio.h>

void showHelp()
{
    textcolor(1);
    gotoxy(16, 0);
    printf("NineGaps");
    gotoxy(0, 3);
    printf("1. Place numbers from 1 to 9 in the\n   missing gaps.");
    gotoxy(0, 6);
    printf("2. All numbers must be used only once.");
    gotoxy(0, 8);
    printf("3. All calculations must be correct to\n   win the game.");
    gotoxy(0, 11);
    printf("4. Use WASD keys to move on the board,\n   press the number keys to place the\n   numbers.");

    textcolor(11);
    gotoxy(9, 17);
    printf("Press any key to start!");
    cgetc();
}

int main()
{
    Board board;

    initScreen();
    showHelp();
    clrscr();
    gameLoop(&board);

    return 0;
}
