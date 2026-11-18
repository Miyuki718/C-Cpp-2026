
#include "ui.h"
#include "game.h"
#include "common.h"
#include "raylib.h"

#undef BLACK
#undef WHITE

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 680

#define CELL_SIZE 40

#define BOARD_LEFT 40
#define BOARD_TOP 70

static const struct Color BOARD_COLOR = {
    222, 184, 135, 255
};

static const struct Color STONE_BLACK_COLOR = {
    25, 25, 25, 255
};

static const struct Color STONE_WHITE_COLOR = {
    245, 245, 245, 255
};

static const struct Color TEXT_COLOR = {
    35, 35, 35, 255
};

void uiInit(void)
{
    InitWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "Gomoku"
    );

    SetTargetFPS(60);
}

void uiClose(void)
{
    CloseWindow();
}

int uiWindowShouldClose(void)
{
    return WindowShouldClose();
}




// 绘制棋盘
static void drawBoard(void)
{
    DrawRectangle(
        0, 0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        BOARD_COLOR
    );

    // 绘制水平线和垂直线
    for (int i = 0; i < BOARD_SIZE; i++) {

        int x = BOARD_LEFT + i * CELL_SIZE;
        int y = BOARD_TOP + i * CELL_SIZE;

        // 水平线
        DrawLine(
            BOARD_LEFT,
            y,
            BOARD_LEFT + (BOARD_SIZE - 1) * CELL_SIZE,
            y,
            DARKBROWN
        );

        // 垂直线
        DrawLine(
            x,
            BOARD_TOP,
            x,
            BOARD_TOP + (BOARD_SIZE - 1) * CELL_SIZE,
            DARKBROWN
        );
    }
}


// 绘制棋子
static void drawStones(const Game *game)
{
    for (int row = 0; row < BOARD_SIZE; row++) {

        for (int col = 0; col < BOARD_SIZE; col++) {

            int x = BOARD_LEFT + col * CELL_SIZE;
            int y = BOARD_TOP + row * CELL_SIZE;

            // 判断是否为黑棋
            if (game->board[row][col] == BLACK) {

                DrawCircle(
                    x, y, 14,
                    STONE_BLACK_COLOR
                );
            }

            // 判断是否为白棋
            else if (game->board[row][col] == WHITE) {

                DrawCircle(
                    x, y, 14,
                    STONE_WHITE_COLOR
                );

                DrawCircleLines(
                    x, y, 14,
                    DARKGRAY
                );
            }
        }
    }
}

// 绘制游戏状态
static void drawStatus(const Game *game)
{
    if (game->status == GAME_BLACK_WIN) {

        DrawText(
            "BLACK WINS!",
            20, 20, 24,
            DARKGREEN
        );

    }
    else if (game->status == GAME_WHITE_WIN) {

        DrawText(
            "WHITE WINS!",
            20, 20, 24,
            DARKGREEN
        );

    }
    else if (game->status == GAME_DRAW) {

        DrawText(
            "DRAW!",
            20, 20, 24,
            DARKGREEN
        );

    }
    else if (game->currentPlayer == BLACK) {

        DrawText(
            "BLACK TURN",
            20, 20, 24,
            TEXT_COLOR
        );

    }
    else {

        DrawText(
            "WHITE TURN",
            20, 20, 24,
            DARKGRAY
        );
    }

}


// 绘制整个游戏
void uiDrawGame(const Game *game)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawBoard();

    drawStones(game);

    drawStatus(game);

    EndDrawing();
}

int uiGetClickedMove(Move *move)
{
    // 只处理鼠标左键刚刚按下的那一帧
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return 0;
    }

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    // 鼠标相对于棋盘起点的位置
    int localX = mouseX - BOARD_LEFT;
    int localY = mouseY - BOARD_TOP;

    // 第 0 条线到最后一条线的距离
    int boardSpan = (BOARD_SIZE - 1) * CELL_SIZE;
    int halfCell = CELL_SIZE / 2;

    // 允许点击最外侧交点周围半格以内的区域
    if (localX < -halfCell || localX >= boardSpan + halfCell ||
        localY < -halfCell || localY >= boardSpan + halfCell) {
        return 0;
        }

    // 换算成距离最近的交点
    int col = (localX + halfCell) / CELL_SIZE;
    int row = (localY + halfCell) / CELL_SIZE;

    // 再检查一次，确保行列不会越界
    if (row < 0 || row >= BOARD_SIZE ||
        col < 0 || col >= BOARD_SIZE) {
        return 0;
        }

    move->row = row;
    move->col = col;

    return 1;
}