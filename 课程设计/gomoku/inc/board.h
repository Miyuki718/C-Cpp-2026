#ifndef GOMOKU_BOARD_H
#define GOMOKU_BOARD_H

#include "common.h"

void initBoard(int board[BOARD_SIZE][BOARD_SIZE]);

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]);

int isInsideBoard(int row, int col);

int placeStone(int board[BOARD_SIZE][BOARD_SIZE],int row,int col,Player player);

void undoMove(int board[BOARD_SIZE][BOARD_SIZE],int row,int col);

#endif