#include "menu.h"
#include "config.h"  // Pentru SCREEN_WIDTH și SCREEN_HEIGHT
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

static bool gameStarted = false;
static bool exitRequested = false;
static bool showHowToPlay = false;
static float menuTime = 0.0f;

void InitMenu(void) {
    gameStarted = false;
    exitRequested = false;
    showHowToPlay = false;
    menuTime = 0.0f;
}

void UpdateMenu(void) {
    menuTime += GetFrameTime();
    
    if (!showHowToPlay) {
        if (IsKeyPressed(KEY_ENTER)) {
            gameStarted = true;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            exitRequested = true;
        }
        if (IsKeyPressed(KEY_H)) {
            showHowToPlay = true;
        }
    } else {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE)) {
            showHowToPlay = false;
        }
    }
}

void DrawMenu(void) {
    // Desenam fundalul cu gradient animat
    Color topColor = BLACK;
    Color bottomColor = (Color){0, 50, 0, 255}; // Verde inchis
    
    for(int y = 0; y < SCREEN_HEIGHT; y++) {
        float t = (float)y / SCREEN_HEIGHT;
        float wave = sinf(menuTime + t * 5) * 0.1f;
        Color lineColor = ColorLerp(topColor, bottomColor, t + wave);
        DrawLine(0, y, SCREEN_WIDTH, y, lineColor);
    }
    
    if (showHowToPlay) {
        // Desenam instructiunile de joc
        const char* instructions[] = {
            "Cum se joaca Snake cu intrebari:",
            "",
            "1. Foloseste sagetile pentru a controla sarpele",
            "2. Mananca mancarea pentru a creste scorul",
            "3. Raspunde corect la intrebari pentru a creste",
            "4. Evita sa te lovesti de pereti sau de tine insuti",
            "",
            "Apasa ESC sau BACKSPACE pentru a reveni la meniu"
        };
        
        // Desenam un fundal semi-transparent pentru text
        DrawRectangle(SCREEN_WIDTH/2 - 250, 80, 500, 300, (Color){0, 0, 0, 200});
        
        int startY = 100;
        for (int i = 0; i < 8; i++) {
            int textWidth = MeasureText(instructions[i], 20);
            DrawText(instructions[i], (SCREEN_WIDTH - textWidth) / 2 + 1, startY + i * 30 + 1, 20, (Color){0, 255, 0, 50});
            DrawText(instructions[i], (SCREEN_WIDTH - textWidth) / 2, startY + i * 30, 20, WHITE);
        }
    } else {
        // Titlu cu efect de umbra si stralucire animata
        float glowIntensity = (sinf(menuTime * 2) + 1) * 0.5f;
        Color glowColor = (Color){0, 255, 0, (unsigned char)(glowIntensity * 100)};
        
        DrawText("SNAKE CU INTREBARI", 202, 102, 40, DARKGRAY);  // umbra
        DrawText("SNAKE CU INTREBARI", 201, 101, 40, glowColor); // stralucire
        DrawText("SNAKE CU INTREBARI", 200, 100, 40, GREEN);     // text principal
        
        // Butoane cu efect de hover si animatie
        int buttonWidth = 300;
        int buttonX = SCREEN_WIDTH/2 - buttonWidth/2;
        Rectangle playButton = {buttonX, 200, buttonWidth, 30};
        Rectangle howToPlayButton = {buttonX, 240, buttonWidth, 30};
        Rectangle exitButton = {buttonX, 280, buttonWidth, 30};
        
        Vector2 mousePos = GetMousePosition();
        Color playColor = CheckCollisionPointRec(mousePos, playButton) ? 
            ColorLerp(WHITE, GREEN, (sinf(menuTime * 5) + 1) * 0.5f) : WHITE;
        Color howToPlayColor = CheckCollisionPointRec(mousePos, howToPlayButton) ? 
            ColorLerp(WHITE, YELLOW, (sinf(menuTime * 5) + 1) * 0.5f) : WHITE;
        Color exitColor = CheckCollisionPointRec(mousePos, exitButton) ? 
            ColorLerp(WHITE, RED, (sinf(menuTime * 5) + 1) * 0.5f) : WHITE;
        
        // Centrăm textul pentru fiecare buton
        const char* playText = "Apasa ENTER pentru a incepe jocul";
        const char* howToPlayText = "Apasa H pentru instructiuni";
        const char* exitText = "Apasa ESC pentru a iesi";
        
        int playWidth = MeasureText(playText, 20);
        int howToPlayWidth = MeasureText(howToPlayText, 20);
        int exitWidth = MeasureText(exitText, 20);
        
        int playTextX = buttonX + (buttonWidth - playWidth) / 2;
        int howToPlayTextX = buttonX + (buttonWidth - howToPlayWidth) / 2;
        int exitTextX = buttonX + (buttonWidth - exitWidth) / 2;
        
        // Desenăm umbrele și textul centrat
        DrawText(playText, playTextX + 2, 202, 20, DARKGRAY);  // umbra
        DrawText(playText, playTextX, 200, 20, playColor);
        
        DrawText(howToPlayText, howToPlayTextX + 2, 242, 20, DARKGRAY);  // umbra
        DrawText(howToPlayText, howToPlayTextX, 240, 20, howToPlayColor);
        
        DrawText(exitText, exitTextX + 2, 282, 20, DARKGRAY);  // umbra
        DrawText(exitText, exitTextX, 280, 20, exitColor);
        
        // Credits cu efect de fade si fundal semi-transparent
        const char* credits[] = {
            "Proiect Snake realizat de echipa:",
            "",
            "Stancu Patricia-Ioana (312AC)",
            "Mitea Roberta-Elena (314AC)",
            "Sardaru Miruna-Andreea (314AC)",
            "Paraschiv Simona-Georgiana (314AC)",
            "Flores-Botezatu Edyra (314AC)",
            "Dumitrescu Laura (314AC)",
            "",
            "Profesor coordonator:",
            "Conf. Dr. Ing. Caramihai Mihai"
        };
        
        // Desenam un fundal pentru credite
        int creditStartY = SCREEN_HEIGHT - 280;
        int boxWidth = 400;
        int boxX = SCREEN_WIDTH/2 - boxWidth/2;
        DrawRectangle(boxX, creditStartY - 10, boxWidth, 270, (Color){0, 0, 0, 180});
        DrawRectangleLines(boxX, creditStartY - 10, boxWidth, 270, (Color){0, 255, 0, 100});
        
        float creditsFade = (sinf(menuTime) + 1) * 0.5f;
        for (int i = 0; i < 11; i++) {
            int textWidth = MeasureText(credits[i], 20);
            Color creditColor = (Color){200, 255, 200, (unsigned char)(creditsFade * 255)};
            // Titlurile cu verde mai aprins
            if (i == 0 || i == 9) {
                creditColor = GREEN;
            }
            // Calculăm poziția x pentru a centra textul în interiorul dreptunghiului de fundal
            int textX = boxX + (boxWidth - textWidth) / 2;
            DrawText(credits[i], textX, creditStartY + i * 24, 20, creditColor);
        }
    }
}

bool IsGameStarted(void) {
    return gameStarted;
}

bool IsExitRequested(void) {
    return exitRequested;
}

bool IsShowingHowToPlay(void) {
    return showHowToPlay;
}
