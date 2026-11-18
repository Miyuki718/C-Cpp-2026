#ifndef GOMOKU_EVALUATE_H
#define GOMOKU_EVALUATE_H

#include "common.h"

#define EVAL_WIN_SCORE 1000000

int evaluateBoard(const int board[BOARD_SIZE][BOARD_SIZE], Player player);

#endif