#include "snake.h"

void InitSnake(Snake *snake) {
    snake->length = 1;
    snake->position[0] = (Vector2){10, 10};
    snake->dir = RIGHT;
    snake->score = 0;
}

void UpdateSnake(Snake *snake) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->position[i] = snake->position[i - 1];
    }

    if (IsKeyPressed(KEY_UP)) snake->dir = UP;
    if (IsKeyPressed(KEY_DOWN)) snake->dir = DOWN;
    if (IsKeyPressed(KEY_LEFT)) snake->dir = LEFT;
    if (IsKeyPressed(KEY_RIGHT)) snake->dir = RIGHT;

    switch (snake->dir) {
        case UP: snake->position[0].y -= 1; break;
        case DOWN: snake->position[0].y += 1; break;
        case LEFT: snake->position[0].x -= 1; break;
        case RIGHT: snake->position[0].x += 1; break;
    }
}

void GrowSnake(Snake *snake) {
    if (snake->length < MAX_SNAKE_LENGTH) {
        snake->position[snake->length] = snake->position[snake->length - 1];
        snake->length++;
    }
}

void DrawSnake(Snake snake) {
    for (int i = 0; i < snake.length; i++) {
        DrawRectangle(snake.position[i].x * 20, snake.position[i].y * 20, 20, 20, GREEN);
    }
}
