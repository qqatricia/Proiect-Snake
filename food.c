#include "food.h"
#include <stdlib.h>

void SpawnFood(Food *food, Snake snake) {
    food->position.x = rand() % 40;
    food->position.y = rand() % 30;
}

void DrawFood(Food food) {
    DrawRectangle(food.position.x * 20, food.position.y * 20, 20, 20, RED);
}

bool CheckCollision(Snake snake, Food food) {
    return (snake.position[0].x == food.position.x && snake.position[0].y == food.position.y);
}
