#include "snake.h"
#include "config.h"
#include "raylib.h"

void DrawSnake(Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        Vector2 pos = snake->positions[i];
        DrawRectangle(pos.x * CELL_SIZE, pos.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, i == 0 ? DARKGREEN : GREEN);
    }
}
