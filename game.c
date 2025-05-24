#include "raylib.h"
#include "game.h"
#include "food.h"
#include "snake.h"
#include "question.h"
#include "config.h"
#include <stdbool.h>

static Snake snake;
static Food food;
static bool pauseGame = false;
static bool gameOver = false;

void InitGame() {
    snake.length = 1;
    snake.positions[0] = (Vector2){SCREEN_WIDTH / (2 * CELL_SIZE), SCREEN_HEIGHT / (2 * CELL_SIZE)};
    snake.direction = (Vector2){1, 0};

    SpawnFood(&food, snake);
    pauseGame = false;
    gameOver = false;
}

void UpdateGame() {
    if (gameOver || pauseGame) return;

    // Mutați corpul șarpelui
    for (int i = snake.length - 1; i > 0; i--) {
        snake.positions[i] = snake.positions[i - 1];
    }

    // Mutați capul șarpelui
    snake.positions[0].x += snake.direction.x;
    snake.positions[0].y += snake.direction.y;

    if (CheckWallCollision()) {
        gameOver = true;
    }

    // Coliziune cu corpul (optional)
    for (int i = 1; i < snake.length; i++) {
        if (snake.positions[0].x == snake.positions[i].x &&
            snake.positions[0].y == snake.positions[i].y) {
            gameOver = true;
            break;
        }
    }

    if (snake.positions[0].x == food.position.x && snake.positions[0].y == food.position.y) {
        pauseGame = true;
        ShowQuestion();
    }
}

void DrawGame() {
    DrawSnake(&snake);
    DrawFood(food);

    DrawText(TextFormat("Score: %d", snake.length - 1), 10, 10, 20, BLACK);

    if (pauseGame) {
        DrawText("Apasati tasta 1 pentru prima varianta si tasta 2 pentru a doua varianta", SCREEN_WIDTH / 2 - MeasureText("Apasati tasta 1 pentru prima varianta si tasta 2 pentru a doua varianta", 20) / 2, SCREEN_HEIGHT - 40, 20, RED);
    }

    if (gameOver) {
        DrawText("Game Over! Apasati ESC pentru a iesi.", SCREEN_WIDTH / 2 - MeasureText("Game Over! Apasati ESC pentru a iesi.", 20) / 2, SCREEN_HEIGHT / 2, 20, RED);
    }
}

void SetDirection(Vector2 dir) {
    // Previne intoarcerea la 180 grade
    if (pauseGame || gameOver) return;

    if ((dir.x != -snake.direction.x || dir.y != -snake.direction.y)) {
        snake.direction = dir;
    }
}

bool CheckWallCollision() {
    return (snake.positions[0].x < 0 || snake.positions[0].y < 0 ||
            snake.positions[0].x >= SCREEN_WIDTH / CELL_SIZE || snake.positions[0].y >= SCREEN_HEIGHT / CELL_SIZE);
}

void ResumeGame(bool correctAnswer) {
    if (correctAnswer) {
        if (snake.length < MAX_SNAKE_LENGTH)
            snake.length++;
    }
    SpawnFood(&food, snake);
    pauseGame = false;
}
