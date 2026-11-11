#ifndef GOMOKU_GAME_H
#define GOMOKU_GAME_H

#include "common.h"

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    Player currentPlayer;
    GameStatus status;
    GameMode mode;
    AIDifficulty difficulty;
    Move history[MAX_MOVES];
    int moveCount;

} Game;

void initGame(Game *game, GameMode mode, AIDifficulty difficulty);

int gamePlayMove(Game *game, Move move);

void switchPlayer(Game *game);

int gameUndo(Game *game);

int isGameOver(const Game *game);

#endif