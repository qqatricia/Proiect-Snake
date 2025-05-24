#include "raylib.h"
#include "game.h"
#include "menu.h"
#include "question.h"
#include "config.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake with Questions");
    SetTargetFPS(10);

    InitMenu();
    InitGame();
    InitQuestions();

    while (!WindowShouldClose())
    {
        if (IsMenuActive())
        {
            UpdateMenu();
        }
        else
        {
            // Gestionează inputul global
            if (!IsQuestionActive())  // Dacă nu e întrebarea afișată
            {
                if (IsKeyDown(KEY_RIGHT)) SetDirection((Vector2){1,0});
                else if (IsKeyDown(KEY_LEFT)) SetDirection((Vector2){-1,0});
                else if (IsKeyDown(KEY_UP)) SetDirection((Vector2){0,-1});
                else if (IsKeyDown(KEY_DOWN)) SetDirection((Vector2){0,1});
            }
            else
            {
                bool answeredCorrect = HandleQuestionInput();
                if (answeredCorrect || IsQuestionAnswered()) {
                    ResumeGame(answeredCorrect);
                }
            }
            
            UpdateGame();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsMenuActive())
        {
            DrawMenu();
        }
        else
        {
            DrawGame();
            if (IsQuestionActive())
                DrawQuestion();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
