
#ifndef GOMOKU_COMMON_H
#define GOMOKU_COMMON_H

#define BOARD_SIZE 15
#define MAX_MOVES (BOARD_SIZE * BOARD_SIZE)

// 棋子类型
typedef enum {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
} Player;

// 落子位置
typedef struct {
    int row;
    int col;
} Move;

// 游戏模式
typedef enum {
    MODE_PVP,
    MODE_PVE
} GameMode;

// AI 难度
typedef enum {
    AI_EASY,
    AI_HARD
} AIDifficulty;

// 游戏状态
typedef enum {
    GAME_PLAYING,
    GAME_BLACK_WIN,
    GAME_WHITE_WIN,
    GAME_DRAW
} GameStatus;

#endif
