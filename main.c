#include "raylib.h"
#include "game.h"
#include "menu.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake cu intrebari");
    InitMenu();

    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        if (IsMenuActive()) {
            UpdateMenu();
            BeginDrawing();
            ClearBackground(BLACK);
            DrawMenu();
            EndDrawing();
        } else {
            UpdateGame();
            BeginDrawing();
            ClearBackground(BLACK);
            DrawGame();
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
