#include "food.h"
#include "config.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

static bool PositionInSnake(Vector2 pos, Snake snake) {
    for (int i = 0; i < snake.length; i++) {
        if (snake.positions[i].x == pos.x && snake.positions[i].y == pos.y) {
            return true;
        }
    }
    return false;
}

void SpawnFood(Food *food, Snake snake) {
    int maxX = SCREEN_WIDTH / CELL_SIZE;
    int maxY = SCREEN_HEIGHT / CELL_SIZE;

    Vector2 pos;
    do {
        pos.x = rand() % maxX;
        pos.y = rand() % maxY;
    } while (PositionInSnake(pos, snake));

    food->position = pos;
}

void DrawFood(Food food) {
    DrawRectangle(food.position.x * CELL_SIZE, food.position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
}
