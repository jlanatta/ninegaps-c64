#include "game.h"
#include "screen.h"

static Board board;

int main() {
    setupScreen();
    setupBoard(&board);
    drawBoard(&board);
    return 0;
}
