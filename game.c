#include "game.h"
#include "snake.h"
#include "food.h"
#include "question.h"
#include "raylib.h"

void RunGame(GameState *gameState) {
    static bool initialized = false;
    static Snake snake;
    static Food food;
    static Question question;
    static bool questionActive = false;
    static bool answerCorrect = false;

    if (!initialized) {
        InitSnake(&snake);
        SpawnFood(&food, snake);
        LoadQuestions("questions.txt");
        initialized = true;
    }

    if (questionActive) {
        DrawText(question.text, 100, 200, 20, WHITE);
        DrawText(question.options[0], 120, 240, 20, GREEN);
        DrawText(question.options[1], 120, 280, 20, GREEN);

        if (IsKeyPressed(KEY_ONE)) {
            answerCorrect = (question.correctAnswer == 0);
            questionActive = false;
        } else if (IsKeyPressed(KEY_TWO)) {
            answerCorrect = (question.correctAnswer == 1);
            questionActive = false;
        }

        return;
    }

    UpdateSnake(&snake);

    if (CheckCollision(snake, food)) {
        question = GetRandomQuestion();
        questionActive = true;
        if (answerCorrect) {
            GrowSnake(&snake);
            snake.score++;
        }
        SpawnFood(&food, snake);
    }

    DrawSnake(snake);
    DrawFood(food);
    DrawText(TextFormat("Score: %d", snake.score), 10, 10, 20, YELLOW);
}
