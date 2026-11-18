#include "game.h"
#include "ui.h"
#include "search.h"

int main(void)
{
    Game game;

    initGame(&game, MODE_PVE, AI_EASY);
    uiInit();

    while (!uiWindowShouldClose()) {
        if (game.mode == MODE_PVE && game.status == GAME_PLAYING && game.currentPlayer == WHITE){
            Move move = bestMove(game.board, 2, WHITE);
            gamePlayMove(&game, move);
        } else {
            Move move;

            if (uiGetClickedMove(&move)) {
                gamePlayMove(&game, move);
            }
        }

        uiDrawGame(&game);
    }

    uiClose();
    return 0;
}