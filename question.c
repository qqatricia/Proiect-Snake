#include "question.h"
#include <raylib.h>

static Question currentQuestion;

void InitQuestions(void) {
    // Exemplu inițializare întrebare, poți extinde să încarci din fișier
    currentQuestion.active = false;
    currentQuestion.answered = false;
}

bool IsQuestionActive(void) {
    return currentQuestion.active;
}

void ShowQuestion(void) {
    if (!currentQuestion.active) return;

    DrawText(currentQuestion.text, 50, 50, 20, BLACK);
    DrawText("1) ", 50, 100, 20, DARKGRAY);
    DrawText(currentQuestion.option1, 80, 100, 20, DARKGRAY);
    DrawText("2) ", 50, 140, 20, DARKGRAY);
    DrawText(currentQuestion.option2, 80, 140, 20, DARKGRAY);
    DrawText("Apasă tasta 1 sau 2 pentru a răspunde", 50, 180, 15, RED);
}

void DrawQuestion(void) {
    ShowQuestion();
}

bool HandleQuestionInput(void) {
    if (!currentQuestion.active) return false;

    if (IsKeyPressed(KEY_ONE)) {
        currentQuestion.answered = true;
        currentQuestion.active = false;
        return currentQuestion.correctOption == 1;
    }
    else if (IsKeyPressed(KEY_TWO)) {
        currentQuestion.answered = true;
        currentQuestion.active = false;
        return currentQuestion.correctOption == 2;
    }
    return false;
}

bool IsQuestionAnswered(void) {
    return currentQuestion.answered;
}
