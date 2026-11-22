//
// Created by songy on 2026/11/11.
//

#include "search.h"
#include "evaluate.h"
#include "rules.h"
#include "board.h"
static int candidates(int board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    int isCandidate = 0;
    int direction[12][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1},{-2,0},{2,0},{0,-2},{0,2}};
    for (int x=0; x<12; x++) {
        if (isInsideBoard(row+direction[x][0], col+direction[x][1]) && board[row+direction[x][0]][col+direction[x][1]] != EMPTY) {
            isCandidate = 1;
        }
    }
    return isCandidate;
}

static int nextMoveWin(int board[BOARD_SIZE][BOARD_SIZE], Player player) {
    int won = 1;
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] != EMPTY) {
                continue;
            }
            board[i][j] = player;
            if (checkWin(board, i, j, player)) {
                board[i][j] = EMPTY;
                return 1;
            } else {
                board[i][j] = EMPTY;
                won = 0;
            }
        }
    }
    if (!won) {
        return 0;
    }
}

static int minimax(int board[BOARD_SIZE][BOARD_SIZE], int depth, Player currentPlayer, Player aiPlayer, int alpha, int beta, int ply) {
    int hasEmpty = 0;
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                hasEmpty = 1;
                continue;
            }

            if (checkWin(board, i, j, board[i][j])) {
                if (board[i][j] == aiPlayer) {
                    return 10000000-ply;
                } else {
                    return -10000000+ply;
                }
            }
        }
    }
    if (hasEmpty == 0) {    //draw
        return 0;
    }

    if (depth <=0) {
        if (nextMoveWin(board, currentPlayer)) {
            if (currentPlayer == aiPlayer) {
                return 10000000 - (ply + 1);
            } else {
                return -10000000 + (ply + 1);
            }
        } else {
            return evaluateBoard(board, aiPlayer);
        }

    }

    int bestScore;
    if (currentPlayer == aiPlayer) {
        bestScore = -10000000;
    } else {
        bestScore = 10000000;
    }

    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (!candidates(board, i, j)) {
                continue;
            }
            if (board[i][j] == EMPTY) {
                board[i][j] = currentPlayer;
                Player nextPlayer = (currentPlayer == BLACK)?WHITE:BLACK;
                int score = minimax(board, depth-1, nextPlayer, aiPlayer, alpha, beta, ply+1);
                board[i][j] = EMPTY;

                if (currentPlayer == aiPlayer) {
                    if (score > bestScore) {
                        bestScore = score;
                    }
                    if (alpha<bestScore) {
                        alpha = bestScore;
                    }
                } else {
                    if (score < bestScore) {
                        bestScore = score;
                    }
                    if (beta > bestScore) {
                        beta = bestScore;
                    }
                }

                if (alpha >= beta) {
                    return bestScore;
                }
            }
        }
    }
    return bestScore;

}

Move bestMove(int board[BOARD_SIZE][BOARD_SIZE], int depth, Player aiPlayer) {
    int bestScore = -10000000;
    Move bestMove = {-1, -1};
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] != EMPTY) {
                continue;
            }
            if(!candidates(board, i, j)) {
                continue;
            }

            board[i][j] = aiPlayer;
            int win = checkWin(board, i, j, aiPlayer);
            board[i][j] = EMPTY;
            if (win) {
                bestMove.row=i;
                bestMove.col=j;
                return bestMove;
            }

        }
    }
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] != EMPTY) {
                continue;
            }
            if(!candidates(board, i, j)) {
                continue;
            }
            board[i][j] = aiPlayer;
            Player opponent = (aiPlayer == BLACK) ? WHITE : BLACK;
            int score = minimax(board, depth - 1, opponent, aiPlayer, bestScore, 1000000000, 1);
            board[i][j] = EMPTY;

            if (bestMove.row == -1 || score > bestScore) {
                bestScore = score;
                bestMove.row = i;
                bestMove.col = j;
            }
        }
    }
    return bestMove;
}