
#ifndef GOMOKU_UI_H
#define GOMOKU_UI_H

#include "game.h"

void uiInit(void);

void uiClose(void);

int uiWindowShouldClose(void);

void uiDrawGame(const Game *game);
int uiGetClickedMove(Move *move);

#endif
