#ifndef GAME_H
#define GAME_H

typedef enum { MENU, PLAYING, EXIT } GameState;

void RunGame(GameState *gameState);

#endif
