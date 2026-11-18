
#include "evaluate.h"
#include "board.h"
#include "rules.h"
#include "common.h"

static int scoreRun(int length, int openEnds) {
    if (length >= 5) {
        return EVAL_WIN_SCORE;
    }
    if (openEnds == 0) {
        return 0;
    }

    switch (length) {
        case 4:
            return openEnds == 2 ? 100000 : 10000;

        case 3:
            return openEnds == 2 ? 1000 : 100;

        case 2:
            return openEnds == 2 ? 100 : 10;

        case 1:
            return openEnds == 2 ? 10 : 1;

        default:
            return 0;
    }
}

static int inBounds(int row, int col){
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

static int evaluatePlayer(const int board[BOARD_SIZE][BOARD_SIZE], Player player) {
    int score = 0;
    int length, openEnds;
    int dr[4] = {-1,-1,-1,0};   /* 1 2 3
                                 * 4 X 5
                                 * 6 7 8*/
    int dc[4] = {-1,0,1,-1};
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            for (int x=0; x<4; x++) {
                if (board[i][j] != player) {
                    continue;
                }
                if (i+dr[x]<0 || j+dc[x]<0 || i + dr[x] >= BOARD_SIZE || j + dc[x] >= BOARD_SIZE || (board[i+dr[x]][j+dc[x]] != player && board[i+dr[x]][j+dc[x]] != EMPTY) ){
                    length = countStone(board, i, j, player, x);
                    if (inBounds(i-length*dr[x], j-length*dc[x])) {
                        openEnds = (board[i-length*dr[x]][j-length*dc[x]] == EMPTY);
                    } else {
                        openEnds = 0;
                    }
                    score += scoreRun(length, openEnds);
                } else if (board[i+dr[x]][j+dc[x]] == EMPTY){
                    length = countStone(board, i, j, player, x);
                    if (inBounds(i-length*dr[x], j-length*dc[x])) {
                        openEnds = 1 + (board[i-length*dr[x]][j-length*dc[x]] == EMPTY);
                    } else {
                        openEnds = 1;
                    }
                    score += scoreRun(length, openEnds);
                }
            }
        }
    }
    return score;
}

int evaluateBoard(const int board[BOARD_SIZE][BOARD_SIZE], Player aiPlayer) {
    int opponent = (aiPlayer == BLACK) ? WHITE : BLACK;
    int aiScore = evaluatePlayer(board, aiPlayer);
    int opponentScore = evaluatePlayer(board, opponent);
    return aiScore - opponentScore;
}

