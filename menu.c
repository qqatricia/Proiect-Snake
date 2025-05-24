#include "menu.h"
#include "raylib.h"

GameState RunMenu(void) {
    DrawText("Snake Quiz Game", 250, 200, 40, WHITE);
    DrawText("Press ENTER to Start", 280, 260, 20, GREEN);
    DrawText("Press ESC to Exit", 300, 300, 20, RED);

    if (IsKeyPressed(KEY_ENTER)) return PLAYING;
    if (IsKeyPressed(KEY_ESCAPE)) return EXIT;

    return MENU;
}
