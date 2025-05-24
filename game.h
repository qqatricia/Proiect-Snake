#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "snake.h"
#include "food.h"

extern bool pauseGame;
extern bool gameOver;

extern Snake snake;
extern Food food;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void ResumeGame(bool correctAnswer);

#endif // GAME_H
