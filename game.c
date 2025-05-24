#include "game.h"
#include "question.h"
#include <raylib.h>

bool pauseGame = false;
bool gameOver = false;

void InitGame(void) {
    pauseGame = false;
    gameOver = false;
    // Inițializează alte elemente ale jocului (sarpe, scor etc)
}

void UpdateGame(void) {
    if (gameOver) return;

    if (pauseGame) {
        ShowQuestion();
        return;
    }

    // Logica jocului când nu este pauză:
    // - actualizarea poziției șarpelui
    // - detectarea coliziunilor
    // - alte mecanici de joc

    if (IsQuestionActive()) {
        ShowQuestion();
    }
}

void DrawGame(void) {
    ClearBackground(RAYWHITE);

    // Desenează elementele jocului (ex: sarpe, mâncare, scor)
    // ...

    if (pauseGame) {
        DrawQuestion();
    }
}

void ResumeGame(bool correctAnswer) {
    pauseGame = false;
    if (!correctAnswer) {
        gameOver = true;
    }
}
