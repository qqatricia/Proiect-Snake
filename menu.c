#include "menu.h"
#include "raylib.h"
#include "game.h"

static bool menuActive = true;
static int selected = 0;

void InitMenu(void) {
    menuActive = true;
    selected = 0;
}

bool IsMenuActive(void) {
    return menuActive;
}

void UpdateMenu(void) {
    if (IsKeyPressed(KEY_DOWN)) {
        selected = (selected + 1) % 2;
    }
    if (IsKeyPressed(KEY_UP)) {
        selected = (selected + 1) % 2; // same cycling
    }
    if (IsKeyPressed(KEY_ENTER)) {
        if (selected == 0) {
            menuActive = false;
            InitGame();
        } else if (selected == 1) {
            CloseWindow();
            exit(0);
        }
    }
}

void DrawMenu(void) {
    const char *options[2] = {"Start Game", "Exit"};
    DrawText("Snake cu Intrebari", 80, 100, 40, LIGHTGRAY);
    for (int i = 0; i < 2; i++) {
        Color col = (i == selected) ? YELLOW : DARKGRAY;
        DrawText(options[i], 150, 200 + i * 50, 30, col);
    }
}
