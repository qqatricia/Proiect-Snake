#include "food.h"
#include "config.h"    // inclus corect
#include <stdlib.h>
#include "utils.h"

void InitFood(Food* food) {
    SpawnFood(food);
}

void SpawnFood(Food* food) {
    int gridX = rand() % (SCREEN_WIDTH / CELL_SIZE);
    int gridY = rand() % (SCREEN_HEIGHT / CELL_SIZE);
    food->position.x = gridX * CELL_SIZE;
    food->position.y = gridY * CELL_SIZE;
    food->points = (rand() % 2) + 1; // 1 sau 2 puncte
}

void DrawFood(const Food* food) {
    Color color = (food->points == 1) ? RED : ORANGE;
    DrawRectangleV(food->position, (Vector2){CELL_SIZE, CELL_SIZE}, color);
}

bool CheckFoodEaten(const Food* food, Vector2 snakeHead) {
    return Vector2Equals(food->position, snakeHead);
}
