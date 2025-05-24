#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "config.h"

extern bool pauseGame;
extern bool gameOver;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void ResumeGame(bool correctAnswer);

#endif // GAME_H
