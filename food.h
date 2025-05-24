#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>

typedef struct {
    Vector2 position;
    int points; // 1 sau 2
} Food;

void InitFood(Food* food);
void SpawnFood(Food* food);
void DrawFood(const Food* food);
bool CheckFoodEaten(const Food* food, Vector2 snakeHead);

#endif // FOOD_H
