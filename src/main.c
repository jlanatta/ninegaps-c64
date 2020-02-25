#include "game.h"
#include "screen.h"

int main()
{
    Board board;

    initScreen();
    initBoard(&board);
    drawBoard(&board);
    gameLoop(&board);
    return 0;
}
