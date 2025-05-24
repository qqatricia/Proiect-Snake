#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define MAX_SNAKE_LENGTH 100

typedef struct {
    Vector2 positions[MAX_SNAKE_LENGTH];
    int length;
    Vector2 direction;
} Snake;

void DrawSnake(Snake *snake);

#endif // SNAKE_H
