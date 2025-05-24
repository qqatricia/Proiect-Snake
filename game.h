#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "food.h"
#include "snake.h"
#include "question.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define CELL_SIZE 20

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetDirection(Vector2 dir);
bool CheckWallCollision(void);

extern bool pauseGame;
extern bool gameOver;

#endif
