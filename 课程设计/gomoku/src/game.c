//
// Created by songy on 2026/11/11.
//

#include "game.h"
#include "board.h"
#include "rules.h"

void initGame(Game *game, GameMode mode, AIDifficulty difficulty) {
    initBoard(game->board);
    game->currentPlayer = BLACK;
    game->status = GAME_PLAYING;
    game->mode = mode;
    game->difficulty = difficulty;
    game->moveCount = 0;
}

int gamePlayMove(Game *game, Move move) {
    if (game->status != GAME_PLAYING) {
        return 0;
    }

    placeStone(game->board, move.row, move.col, game->currentPlayer);

    game->history[game->moveCount] = move;

    if (game->moveCount == MAX_MOVES) {
        game->status = GAME_DRAW;
    }

    if (checkWin(game->board, move.row, move.col, game->currentPlayer)) {
        if (game->currentPlayer == BLACK) {
            game->status = GAME_BLACK_WIN;
        } else {
            game->status = GAME_WHITE_WIN;
        }
    }

    return 1;
}

void switchPlayer(Game *game) {
    if (game->currentPlayer == BLACK) {
        game->currentPlayer = WHITE;
    } else {
        game->currentPlayer = BLACK;
    }
}

int gameUndo(Game *game) {
    if (!game->history) {
        return 0;
    }
    game->moveCount--;
    game->currentPlayer = 
}

int isGameOver(const Game *game) {
    return game->status != GAME_PLAYING;
}