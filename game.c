#include "game.h"
#include "menu.h"

static Snake snake;
static Food food;
static Question currentQuestion;
static int score = 0;

bool pauseGame = false;
bool gameOver = false;

static void ResetGame(void) {
    InitGame();
    score = 0;
    pauseGame = false;
    gameOver = false;
}

void InitGame(void) {
    snake.length = 1;
    snake.positions[0] = (Vector2){10, 10};
    snake.direction = (Vector2){1, 0};
    SpawnFood(&food, snake);
    LoadQuestions("questions.txt");
}

void UpdateGame(void) {
    if (pauseGame || gameOver) return;

    // Muta sarpele
    for (int i = snake.length - 1; i > 0; i--)
        snake.positions[i] = snake.positions[i - 1];
    snake.positions[0].x += snake.direction.x;
    snake.positions[0].y += snake.direction.y;

    if (CheckWallCollision()) {
        gameOver = true;
        pauseGame = true;
    }

    // Verifică dacă a mâncat mâncarea
    if ((int)snake.positions[0].x == (int)food.position.x &&
        (int)snake.positions[0].y == (int)food.position.y) {
        
        if (score < GetQuestionsCount()) {
            currentQuestion = GetRandomQuestion(score);
        } else {
            currentQuestion = GetRandomQuestion(0);
        }
        pauseGame = true;
    }
}

void DrawGame(void) {
    DrawText(TextFormat("Scor: %d", score), 10, 10, 20, GREEN);

    DrawSnake(&snake);
    DrawFood(&food);

    if (pauseGame && !gameOver) {
        // Desenează întrebarea și instrucțiuni pentru răspuns
        DrawText(currentQuestion.question, 10, SCREEN_HEIGHT / 2 - 40, 20, RAYWHITE);
        DrawText(TextFormat("1: %s", currentQuestion.option1), 10, SCREEN_HEIGHT / 2, 20, LIGHTGRAY);
        DrawText(TextFormat("2: %s", currentQuestion.option2), 10, SCREEN_HEIGHT / 2 + 30, 20, LIGHTGRAY);
        DrawText("Apasati tasta 1 pentru prima varianta", 10, SCREEN_HEIGHT / 2 + 70, 18, YELLOW);
        DrawText("Apasati tasta 2 pentru a doua varianta", 10, SCREEN_HEIGHT / 2 + 100, 18, YELLOW);
    }

    if (gameOver) {
        DrawText("GAME OVER!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, 40, RED);
        DrawText("Apasa ENTER pentru restart", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 50, 20, WHITE);
        if (IsKeyPressed(KEY_ENTER)) {
            ResetGame();
        }
    }
}

void SetDirection(Vector2 dir) {
    if (!pauseGame && !gameOver) snake.direction = dir;
}

bool CheckWallCollision(void) {
    return (snake.positions[0].x < 0 || snake.positions[0].y < 0 ||
            snake.positions[0].x >= SCREEN_WIDTH / CELL_SIZE || snake.positions[0].y >= SCREEN_HEIGHT / CELL_SIZE);
}

void AnswerQuestion(int answer) {
    if (!pauseGame) return;

    if ((answer == 1 && currentQuestion.correctOption == 1) ||
        (answer == 2 && currentQuestion.correctOption == 2)) {
        // Raspuns corect
        score++;
        if (snake.length < 100) snake.length++;
    }
    SpawnFood(&food, snake);
    pauseGame = false;
}
