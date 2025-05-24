#include "raylib.h"
#include "game.h"
#include "menu.h"

int main(void) {
    InitWindow(800, 600, "Snake Quiz Game");
    SetTargetFPS(10);

    GameState gameState = MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState) {
            case MENU:
                gameState = RunMenu();
                break;
            case PLAYING:
                RunGame(&gameState);
                break;
            case EXIT:
                CloseWindow();
                return 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
