#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include "snake.h"

typedef struct {
    Vector2 position;
} Food;

void SpawnFood(Food *food, Snake snake);
void DrawFood(Food food);
bool CheckCollision(Snake snake, Food food);

#endif
