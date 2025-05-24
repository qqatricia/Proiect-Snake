#include "menu.h"
#include <raylib.h>
#include <stdlib.h>

static bool gameStarted = false;
static bool exitRequested = false;

void InitMenu(void) {
    gameStarted = false;
    exitRequested = false;
}

void UpdateMenu(void) {
    if (IsKeyPressed(KEY_ENTER)) {
        gameStarted = true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        exitRequested = true;
    }
}

void DrawMenu(void) {
    ClearBackground(RAYWHITE);
    DrawText("SNAKE CU INTREBARI", 200, 100, 40, DARKGREEN);
    DrawText("ENTER - Start Game", 250, 200, 20, DARKGRAY);
    DrawText("ESC - Exit", 250, 240, 20, DARKGRAY);
}

bool IsGameStarted(void) {
    return gameStarted;
}

bool IsExitRequested(void) {
    return exitRequested;
}
