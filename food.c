#include "food.h"
#include <stdlib.h>

void SpawnFood(Food *food, Snake snake) {
    bool validPosition = false;
    while (!validPosition) {
        food->position.x = rand() % (400 / 20);
        food->position.y = rand() % (400 / 20);

        validPosition = true;
        for (int i = 0; i < snake.length; i++) {
            if (snake.positions[i].x == food->position.x && snake.positions[i].y == food->position.y) {
                validPosition = false;
                break;
            }
        }
    }
}

void DrawFood(Food *food) {
    DrawRectangle(food->position.x * 20, food->position.y * 20, 20, 20, RED);
}
