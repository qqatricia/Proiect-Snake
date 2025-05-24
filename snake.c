#include "snake.h"

void DrawSnake(Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        Color col = (i == 0) ? GREEN : DARKGREEN;
        DrawRectangle(snake->positions[i].x * 20, snake->positions[i].y * 20, 20, 20, col);
        // Extra design: draw outline
        DrawRectangleLines(snake->positions[i].x * 20, snake->positions[i].y * 20, 20, 20, BLACK);
    }
}
