//
// Created by songy on 2026/11/11.
//

#include "rules.h"
#include "board.h"

static int countStone(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, Player player, int direction) {
    int count = 0;
    int forward = 0;
    int backward = 0;
    int x = row, y = col;

    int dr[4] = {-1,-1,-1,0};   /* 1 2 3
                                 * 4 X 5
                                 * 6 7 8*/
    int dc[4] = {-1,0,1,-1};

    while (isInsideBoard(row+dr[direction], col+dc[direction]) && board[row+dr[direction]][col+dc[direction]] == player) {
        backward++;
        row += dr[direction];
        col += dc[direction];
    }
    row = x;
    col = y;
    while (isInsideBoard(row-dr[direction], col-dc[direction]) && board[row-dr[direction]][col-dc[direction]] == player) {
        forward++;
        row -= dr[direction];
        col -= dc[direction];
    }

    count = forward+backward+1;
    return count;
}

int checkWin(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, Player player) {
    if (!isInsideBoard(row, col) || board[row][col] != player) {
        return 0;
    } else {
        for (int i=0; i<4; i++) {
            if (countStone(board, row, col, player,i) >= 5){
                return 1;
            }
        }
        return 0;
    }
}

