//
// Created by songy on 2026/11/11.
//

#include "search.h"
#include "evaluate.h"
#include "rules.h"

static int minimax(int board[BOARD_SIZE][BOARD_SIZE], int depth, Player currentPlayer, Player aiPlayer, int alpha, int beta) {
    int hasEmpty = 0;
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                hasEmpty = 1;
                continue;
            }

            if (checkWin(board, i, j, board[i][j])) {
                if (board[i][j] == aiPlayer) {
                    return 10000000;
                } else {
                    return -10000000;
                }
            }
        }
    }
    if (hasEmpty == 0) {    //draw
        return 0;
    }

    if (depth <=0) {
        return evaluateBoard(board, aiPlayer);
    }

    int bestScore;
    if (currentPlayer == aiPlayer) {
        bestScore = -10000000;
    } else {
        bestScore = 10000000;
    }

    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = currentPlayer;
                Player nextPlayer = (currentPlayer == BLACK)?WHITE:BLACK;
                int score = minimax(board, depth-1, nextPlayer, aiPlayer, alpha, beta);
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

            board[i][j] = aiPlayer;
            Player opponent = (aiPlayer == BLACK) ? WHITE : BLACK;
            int score = minimax(board, depth - 1, opponent, aiPlayer, -100000000, 1000000000);
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