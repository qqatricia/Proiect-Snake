#include "raylib.h"
#include "question.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"

#define MAX_QUESTIONS 30

typedef struct {
    char question[128];
    char option1[64];
    char option2[64];
    int correct; // 1 or 2
} Question;

static Question questions[MAX_QUESTIONS];
static int totalQuestions = 0;
static int currentQuestion = 0;
static bool showingQuestion = false;
static bool questionAnswered = false;
static bool lastAnswerCorrect = false;

void InitQuestions() {
    FILE *file = fopen("questions.txt", "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului questions.txt\n");
        exit(1);
    }

    totalQuestions = 0;
    while (fgets(questions[totalQuestions].question, sizeof(questions[totalQuestions].question), file)) {
        if (fgets(questions[totalQuestions].option1, sizeof(questions[totalQuestions].option1), file) &&
            fgets(questions[totalQuestions].option2, sizeof(questions[totalQuestions].option2), file) &&
            fscanf(file, "%d\n", &questions[totalQuestions].correct) == 1) {
            questions[totalQuestions].question[strcspn(questions[totalQuestions].question, "\n")] = 0;
            questions[totalQuestions].option1[strcspn(questions[totalQuestions].option1, "\n")] = 0;
            questions[totalQuestions].option2[strcspn(questions[totalQuestions].option2, "\n")] = 0;
            totalQuestions++;
            if (totalQuestions >= MAX_QUESTIONS) break;
        } else {
            break;
        }
    }
    fclose(file);

    srand(time(NULL));
}

void ShowQuestion() {
    showingQuestion = true;
    questionAnswered = false;
    currentQuestion = rand() % totalQuestions;
}

void DrawQuestion() {
    if (!showingQuestion) return;

    int x = SCREEN_WIDTH / 2 - 300;
    int y = SCREEN_HEIGHT / 3;

    DrawRectangle(x - 10, y - 10, 620, 120, LIGHTGRAY);
    DrawRectangleLines(x - 10, y - 10, 620, 120, DARKGRAY);

    DrawText(questions[currentQuestion].question, x, y, 20, BLACK);
    DrawText(TextFormat("1: %s", questions[currentQuestion].option1), x, y + 30, 18, DARKGREEN);
    DrawText(TextFormat("2: %s", questions[currentQuestion].option2), x, y + 60, 18, DARKGREEN);
    DrawText("Apasati tasta 1 pentru prima varianta si tasta 2 pentru a doua varianta", x, y + 90, 16, RED);
}

bool HandleQuestionInput() {
    if (!showingQuestion || questionAnswered) return false;

    if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_NUM_ONE)) {
        questionAnswered = true;
        lastAnswerCorrect = (questions[currentQuestion].correct == 1);
        showingQuestion = false;
        return lastAnswerCorrect;
    }
    else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_NUM_TWO)) {
        questionAnswered = true;
        lastAnswerCorrect = (questions[currentQuestion].correct == 2);
        showingQuestion = false;
        return lastAnswerCorrect;
    }
    return false;
}

bool IsQuestionActive() {
    return showingQuestion;
}

bool IsQuestionAnswered() {
    return questionAnswered;
}

bool LastAnswerCorrect() {
    return lastAnswerCorrect;
}
