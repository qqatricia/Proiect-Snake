#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define MAX_SNAKE_LENGTH 100

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct {
    Vector2 position[MAX_SNAKE_LENGTH];
    int length;
    Direction dir;
    int score;
} Snake;

void InitSnake(Snake *snake);
void UpdateSnake(Snake *snake);
void GrowSnake(Snake *snake);
void DrawSnake(Snake snake);

#endif
