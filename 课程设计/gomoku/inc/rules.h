#ifndef GOMOKU_RULES_H
#define GOMOKU_RULES_H

#include "common.h"

int checkWin(int board[BOARD_SIZE][BOARD_SIZE],int row,int col,Player player);

int countStone(const int board[BOARD_SIZE][BOARD_SIZE], int row, int col, Player player, int direction);
#endif
