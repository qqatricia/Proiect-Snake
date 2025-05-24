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

void DrawGame() {
    ClearBackground(RAYWHITE);

    if (gameOver) {
        DrawText("Game Over!", 100, 200, 40, RED);
        DrawText(TextFormat("Final Score: %d", score), 100, 250, 30, DARKGRAY);
        return;
    }

    // Desenare sarpe
    for (int i = 0; i < snake.length; i++) {
        DrawRectangle(snake.body[i].x * CELL_SIZE, snake.body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGREEN);
    }

    DrawFood();
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
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
