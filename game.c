// game.c
#include "game.h"
#include "raylib.h"
#include "food.h"
#include "question.h"
#include <stdio.h>

Snake snake;
int score;
bool pauseGame = false;
bool gameOver = false;

void InitGame() {
    snake.length = 1;
    snake.direction = (Vector2){1, 0};
    snake.body[0] = (Vector2){10, 10};
    score = 0;
    pauseGame = false;
    gameOver = false;
}

void UpdateGame() {
    if (gameOver || pauseGame) return;

    // Deplasare corp sarpe
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }

    // Deplasare cap sarpe
    snake.body[0].x += snake.direction.x;
    snake.body[0].y += snake.direction.y;

    // Verificare coliziune cu peretii
    if (CheckWallCollision()) {
        gameOver = true;
        return;
    }

    // Verificare mancare
    if ((int)snake.body[0].x == foodPos.x && (int)snake.body[0].y == foodPos.y) {
        pauseGame = true;
        ShowQuestion();
    }
}

void DrawSnake(Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        Rectangle segment = {
            snake->positions[i].x * CELL_SIZE,
            snake->positions[i].y * CELL_SIZE,
            CELL_SIZE,
            CELL_SIZE
        };

        if (i == 0) {
            // Capul șarpelui – culoare distinctă
            DrawRectangleRec(segment, DARKGREEN);

            // Desenare ochi
            int eyeRadius = 2;
            int eyeOffsetX = 4;
            int eyeOffsetY = 4;

            Vector2 eye1 = {
                segment.x + eyeOffsetX,
                segment.y + eyeOffsetY
            };
            Vector2 eye2 = {
                segment.x + CELL_SIZE - eyeOffsetX,
                segment.y + eyeOffsetY
            };

            DrawCircleV(eye1, eyeRadius, WHITE);
            DrawCircleV(eye2, eyeRadius, WHITE);
        } else {
            // Corpul șarpelui
            DrawRectangleRec(segment, GREEN);
        }
    }
}


void SetDirection(Vector2 dir) {
    if (!pauseGame && !gameOver) snake.direction = dir;
}

void ResumeGame(bool correct) {
    pauseGame = false;
    if (correct) {
        score++;
        snake.length++;
    }
    SpawnFood();
}

bool CheckWallCollision() {
    return (snake.body[0].x < 0 || snake.body[0].y < 0 ||
            snake.body[0].x >= SCREEN_WIDTH / CELL_SIZE || snake.body[0].y >= SCREEN_HEIGHT / CELL_SIZE);
}
