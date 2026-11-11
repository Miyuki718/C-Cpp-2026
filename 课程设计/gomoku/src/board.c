#include "../inc/board.h"
#include <stdio.h>
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]==0) {
                printf("· ");
            } else if (board[i][j] == 1) {
                printf("X ");
            } else if (board[i][j] == 2) {
                printf("O ");
            }
        }
        printf("\n");
    }
}


int isInsideBoard(int row, int col) {
    if (row < BOARD_SIZE && col < BOARD_SIZE && row >= 0 && col >= 0) {
        return 1;   //success
    } else {
        return 0;
    }
}

int PlayStone(int board[BOARD_SIZE][BOARD_SIZE],int row,int col,Player player) {
    if (!isInsideBoard(row, col)||board[row][col] != 0){
        return 0;
    }
    board[row][col] = player;

    return 1;
}

void undoMove(int board[BOARD_SIZE][BOARD_SIZE],int row,int col) {
    if (!isInsideBoard(row, col)) {
        return;
    }

    board[row][col] = 0;
}