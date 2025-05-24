#include "food.h"
#include "config.h"
#include <stdlib.h>

void InitFood(Food* food) {
    SpawnFood(food);
}

void SpawnFood(Food* food) {
    int gridX = rand() % (SCREEN_WIDTH / 20);
    int gridY = rand() % (SCREEN_HEIGHT / 20);
    food->position.x = gridX * 20;
    food->position.y = gridY * 20;
    food->points = (rand() % 2) + 1; // 1 sau 2 puncte
}

void DrawFood(const Food* food) {
    Color color = (food->points == 1) ? RED : ORANGE;
    DrawRectangleV(food->position, (Vector2){20, 20}, color);
}

bool CheckFoodEaten(const Food* food, Vector2 snakeHead) {
    return Vector2Equals(food->position, snakeHead);
}
