#include "snake.h"
#include "config.h"   // inclus
#include "utils.h"

void InitSnake(Snake* snake) {
    snake->length = 5;
    snake->dir = DIR_RIGHT;
    for (int i = 0; i < snake->length; i++) {
        snake->positions[i] = (Vector2){(float)(50 - i * CELL_SIZE), 50.0f};
    }
}

void UpdateSnake(Snake* snake) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->positions[i] = snake->positions[i - 1];
    }
    switch (snake->dir) {
        case DIR_UP:
            snake->positions[0].y -= CELL_SIZE;
            break;
        case DIR_DOWN:
            snake->positions[0].y += CELL_SIZE;
            break;
        case DIR_LEFT:
            snake->positions[0].x -= CELL_SIZE;
            break;
        case DIR_RIGHT:
            snake->positions[0].x += CELL_SIZE;
            break;
    }
}

void DrawSnake(const Snake* snake) {
    for (int i = 0; i < snake->length; i++) {
        DrawRectangleV(snake->positions[i], (Vector2){CELL_SIZE, CELL_SIZE}, GREEN);
    }
}

bool CheckCollisionWithWalls(const Snake* snake) {
    Vector2 head = snake->positions[0];
    if (head.x < 0 || head.x >= SCREEN_WIDTH || head.y < 0 || head.y >= SCREEN_HEIGHT)
        return true;
    return false;
}

bool CheckCollisionWithSelf(const Snake* snake) {
    Vector2 head = snake->positions[0];
    for (int i = 1; i < snake->length; i++) {
        if (Vector2Equals(head, snake->positions[i]))
            return true;
    }
    return false;
}

void GrowSnake(Snake* snake) {
    if (snake->length < MAX_SNAKE_LENGTH) {
        snake->positions[snake->length] = snake->positions[snake->length - 1];
        snake->length++;
    }
}
