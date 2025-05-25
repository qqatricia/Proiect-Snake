#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>
#include "config.h"

extern bool pauseGame;
extern bool gameOver;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void ResumeGame(bool correctAnswer);
void CleanupGame(void);

#endif // GAME_H
