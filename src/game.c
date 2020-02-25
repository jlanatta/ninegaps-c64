#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "screen.h"
#include "utils-random.h"

void initBoard(Board *board)
{
    int i;

    board->currentX = 1;
    board->currentY = 1;
    board->startX = 13;
    board->startY = 6;
    board->won = 0;
    board->hintAmount = 2;

    for (i = 0; i < 9; i++)
    {
        board->tiles[i] = i + 1;
        board->playerTiles[i] = 0;
        board->hintTiles[i] = i;
    }

    strcpy(board->horizontalOperators, "++++--");
    strcpy(board->verticalOperators, "++++--");

    _randomize();
    shuffleIntArray(board->tiles, 9);
    shuffleIntArray(board->hintTiles, 9);
    shuffleCharArray(board->horizontalOperators, 6);
    shuffleCharArray(board->verticalOperators, 6);

    for (i = 0; i < board->hintAmount; i++)
    {
        board->playerTiles[board->hintTiles[i]] = board->tiles[board->hintTiles[i]];
    }
}

void resetBoard(Board *board) {
    int i;
    for (i=0; i<9; i++) {
        board->playerTiles[i] = 0;
    }

    for (i = 0; i < board->hintAmount; i++)
    {
        board->playerTiles[board->hintTiles[i]] = board->tiles[board->hintTiles[i]];
    }
}

void processKey(Board *board)
{
    int x, y;
    int index;
    char c = cgetc();

    switch (c)
    {
    case 'a':
        if (board->currentX > 0)
            board->currentX--;
        break;
    case 's':
        if (board->currentY < 2)
            board->currentY++;
        break;
    case 'd':
        if (board->currentX < 2)
            board->currentX++;
        break;
    case 'w':
        if (board->currentY > 0)
            board->currentY--;
        break;
    case 'r':
        resetBoard(board);
        break;
    case 20:
        index = 3 * board->currentY + board->currentX;
        board->playerTiles[index] = 0;
        break;
    case 'h':
        textcolor(1);
        for (x = 0; x < 3; x++)
        {
            for (y = 0; y < 3; y++)
            {
                gotoxy(x, y);
                printf("%d", board->tiles[3 * y + x]);
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

        index = 3 * board->currentY + board->currentX;

        if (value > 0)
        {
            for (i = 0; i < 10; i++)
            {
                if (board->playerTiles[i] == value)
                {
                    board->playerTiles[i] = 0;
                }
            }

            board->playerTiles[index] = value;
        }
        else
        {
            board->playerTiles[index] = 0;
        }
    }
}

int checkResult(Board *board)
{
    int allRows, allCols;
    allRows = isRowCorrect(board, 0) && isRowCorrect(board, 1) && isRowCorrect(board, 2);
    allCols = isColCorrect(board, 0) && isColCorrect(board, 1) && isColCorrect(board, 2);
    board->won = allRows && allCols;

    return board->won;
}

void showWinnerScreen(Board *board)
{
    textcolor(5);
    gotoxy(15, board->startY + 16);
    printf("YOU WON!!!");

    textcolor(11);
    gotoxy(7, board->startY + 17);
    printf("press any key to continue.");

    cgetc();
}

void gameLoop(Board *board)
{
    while (1)
    {
        clrscr();
        initBoard(board);

        while (!board->won)
        {
            drawBoard(board);
            setCursorOnPlayerPosition(board);
            if (!checkResult(board))
            {
                processKey(board);
            }
        }

        showWinnerScreen(board);
    }
}

int calculate(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    default:
        return 0;
    }
}

ResultType resultTypeForRow(Board *board, int row)
{
    int a, b, c;
    int real, current;

    a = board->playerTiles[3 * row + 0];
    b = board->playerTiles[3 * row + 1];
    c = board->playerTiles[3 * row + 2];
    real = resultForBoardRow(board, row);
    current = currentResultForBoardRow(board, row);

    if (a > 0 && b > 0 && c > 0)
    {
        if (real == current)
        {
            return Right;
        }
        else
        {
            return Wrong;
        }
    }
    else
    {
        return Inconclusive;
    }
}

ResultType resultTypeForCol(Board *board, int col)
{
    int a, b, c;
    int real, current;

    a = board->playerTiles[col + 0];
    b = board->playerTiles[col + 3];
    c = board->playerTiles[col + 6];

    if (a > 0 && b > 0 && c > 0)
    {
        real = resultForBoardCol(board, col);
        current = currentResultForBoardCol(board, col);
        if (real == current)
        {
            return Right;
        }
        else
        {
            return Wrong;
        }
    }
    else
    {
        return Inconclusive;
    }
}

int resultForBoardRow(Board *board, int row)
{
    int a, b, c;
    char op1, op2;

    a = board->tiles[3 * row + 0];
    op1 = board->horizontalOperators[2 * row + 0];
    b = board->tiles[3 * row + 1];
    op2 = board->horizontalOperators[2 * row + 1];
    c = board->tiles[3 * row + 2];

    return calculate(calculate(a, b, op1), c, op2);
}

int resultForBoardCol(Board *board, int col)
{
    int a, b, c;
    char op1, op2;

    a = board->tiles[col + 0];
    op1 = board->verticalOperators[2 * col + 0];
    b = board->tiles[col + 3];
    op2 = board->verticalOperators[2 * col + 1];
    c = board->tiles[col + 6];

    return calculate(calculate(a, b, op1), c, op2);
}

int currentResultForBoardRow(Board *board, int row)
{
    int a, b, c;
    char op1, op2;

    a = board->playerTiles[3 * row + 0];
    op1 = board->horizontalOperators[2 * row + 0];
    b = board->playerTiles[3 * row + 1];
    op2 = board->horizontalOperators[2 * row + 1];
    c = board->playerTiles[3 * row + 2];

    return calculate(calculate(a, b, op1), c, op2);
}

int currentResultForBoardCol(Board *board, int col)
{
    int a, b, c;
    char op1, op2;

    a = board->playerTiles[col + 0];
    op1 = board->verticalOperators[2 * col + 0];
    b = board->playerTiles[col + 3];
    op2 = board->verticalOperators[2 * col + 1];
    c = board->playerTiles[col + 6];

    return calculate(calculate(a, b, op1), c, op2);
}

int isColCorrect(Board *board, int col)
{
    int real, current;

    real = resultForBoardCol(board, col);
    current = currentResultForBoardCol(board, col);

    return real == current;
}

int isRowCorrect(Board *board, int row)
{
    int real, current;

    real = resultForBoardRow(board, row);
    current = currentResultForBoardRow(board, row);

    return real == current;
}