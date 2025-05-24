#include "menu.h"
#include "raylib.h"
#include "config.h"
#include <stdlib.h>

static bool menuActive = true;

void InitMenu(void) {
    menuActive = true;
}

bool IsMenuActive(void) {
    return menuActive;
}

void UpdateMenu(void) {
    if (IsKeyPressed(KEY_ENTER)) {
        menuActive = false;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
        exit(0);
    }
}

void DrawMenu(void) {
    ClearBackground(RAYWHITE);
    DrawText("Snake with Questions", SCREEN_WIDTH / 2 - MeasureText("Snake with Questions", 40) / 2, SCREEN_HEIGHT / 3, 40, DARKGREEN);
    DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to Start", 20) / 2, SCREEN_HEIGHT / 2, 20, DARKGRAY);
    DrawText("Press ESC to Exit", SCREEN_WIDTH / 2 - MeasureText("Press ESC to Exit", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, DARKGRAY);
}
