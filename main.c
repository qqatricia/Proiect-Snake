#include <raylib.h>
#include "config.h"  // deja inclus
#include "game.h"
#include "menu.h"
#include "question.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake cu intrebari");

    InitMenu();
    InitGame();
    InitQuestions();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!IsGameStarted()) {
            UpdateMenu();
            BeginDrawing();
            DrawMenu();
            EndDrawing();

            if (IsExitRequested()) break;
        } else {
            if (!IsQuestionActive()) {
                UpdateGame();
            } else {
                bool answeredCorrect = HandleQuestionInput();
                if (answeredCorrect || IsQuestionAnswered()) {
                    ResumeGame(answeredCorrect);
                }
            }

            BeginDrawing();
            DrawGame();
            EndDrawing();
        }
    }

    // Curăță resursele înainte de a închide fereastra
    CleanupGame();
    CloseWindow();
    return 0;
}
