#include "game.h"
#include "config.h"
#include "snake.h"
#include "food.h"
#include "question.h"
#include "particles.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>

bool pauseGame = false;
bool gameOver = false;
static Snake snake;
static Food food;
static int frameCounter = 0;
static int score = 0;
static int correctAnswers = 0;
static float gameTime = 0.0f;
static ParticleSystem foodParticles;
static ParticleSystem snakeParticles;

// Functie pentru desenarea grilei
static void DrawGameGrid(void) {
    const int cellSize = 20;
    const Color gridColor = (Color){50, 50, 50, 255};  // Gri inchis pentru grila

    // Linii verticale
    for (int x = 0; x <= SCREEN_WIDTH; x += cellSize) {
        DrawLine(x, 0, x, SCREEN_HEIGHT, gridColor);
    }
    
    // Linii orizontale
    for (int y = 0; y <= SCREEN_HEIGHT; y += cellSize) {
        DrawLine(0, y, SCREEN_WIDTH, y, gridColor);
    }
    
    // Desenam un contur mai evident pentru marginea de joc
    const int borderThickness = 2;
    const Color borderColor = (Color){100, 100, 100, 255};  // Gri mai deschis pentru margine
    
    // Marginea de sus
    DrawRectangle(0, 0, SCREEN_WIDTH, borderThickness, borderColor);
    // Marginea de jos
    DrawRectangle(0, SCREEN_HEIGHT - borderThickness, SCREEN_WIDTH, borderThickness, borderColor);
    // Marginea din stanga
    DrawRectangle(0, 0, borderThickness, SCREEN_HEIGHT, borderColor);
    // Marginea din dreapta
    DrawRectangle(SCREEN_WIDTH - borderThickness, 0, borderThickness, SCREEN_HEIGHT, borderColor);
}

void InitGame(void) {
    printf("\n=== Starting Game Initialization ===\n");
    pauseGame = false;
    gameOver = false;  // Asigura-te ca jocul nu incepe in starea game over
    frameCounter = 0;
    score = 0;
    correctAnswers = 0;
    gameTime = 0.0f;
    InitSnake(&snake);
    InitFood(&food);
    InitParticleSystem(&foodParticles);
    InitParticleSystem(&snakeParticles);
    printf("Game state after initialization:\n");
    printf("- pauseGame: %d\n", pauseGame);
    printf("- gameOver: %d\n", gameOver);
    printf("- frameCounter: %d\n", frameCounter);
    printf("- score: %d\n", score);
    printf("- correctAnswers: %d\n", correctAnswers);
    printf("- gameTime: %f\n", gameTime);
    printf("=== Game Initialization Complete ===\n\n");
}

void UpdateGame(void) {
    if (gameOver) {
        if (IsKeyPressed(KEY_ENTER)) {
            // Curata texturile vechi inainte de a reinitia jocul
            UnloadSnakeTextures(&snake);
            InitGame();
            return;
        }
        return;
    }

    if (pauseGame) {
        bool answeredCorrect = HandleQuestionInput();
        if (answeredCorrect || IsQuestionAnswered()) {
            ResumeGame(answeredCorrect);
        }
        return;
    }

    float deltaTime = GetFrameTime();
    gameTime += deltaTime;
    
    // Actualizare particule
    UpdateParticles(&foodParticles, deltaTime);
    UpdateParticles(&snakeParticles, deltaTime);
    
    // Controlul sarpelui - verificam tastele inainte de a actualiza pozitia
    Direction newDir = snake.dir;  // Pastram directia curenta
    
    // Verificam fiecare tasta si actualizam directia doar daca nu e opusa directiei curente
    if (IsKeyPressed(KEY_UP) && snake.dir != DIR_DOWN) {
        newDir = DIR_UP;
    }
    else if (IsKeyPressed(KEY_DOWN) && snake.dir != DIR_UP) {
        newDir = DIR_DOWN;
    }
    else if (IsKeyPressed(KEY_LEFT) && snake.dir != DIR_RIGHT) {
        newDir = DIR_LEFT;
    }
    else if (IsKeyPressed(KEY_RIGHT) && snake.dir != DIR_LEFT) {
        newDir = DIR_RIGHT;
    }
    
    // Actualizam directia sarpelui
    snake.dir = newDir;

    // Actualizeaza pozitia sarpelui la fiecare 10 frame-uri
    frameCounter++;
    if (frameCounter >= 10) {
        frameCounter = 0;
        UpdateSnake(&snake);
        
        // Verificam coliziunea cu peretii
        if (CheckCollisionWithWalls(&snake)) {
            gameOver = true;
            return;
        }
        
        // Verificam coliziunea cu sine insusi
        if (CheckCollisionWithSelf(&snake)) {
            gameOver = true;
            return;
        }
        
        // Verificam coliziunea cu mancarea
        if (CheckCollisionCircleRec(
                (Vector2){food.position.x + 10, food.position.y + 10}, 10,
                (Rectangle){snake.positions[0].x, snake.positions[0].y, 20, 20})) {
            // Emite particule la poziția mâncării
            EmitParticles(&foodParticles, 
                         (Vector2){food.position.x + 10, food.position.y + 10},
                         (Color){255, 255, 0, 255}, 20);
            
            score += 10;
            GrowSnake(&snake);
            MoveFood(&food);
            ShowQuestion();
        }
    }

    // Verificare răspuns la întrebare
    if (IsQuestionActive()) {
        if (HandleQuestionInput()) {
            correctAnswers++;
            // Efect de particule pentru răspuns corect
            for (int i = 0; i < snake.length; i++) {
                EmitParticles(&snakeParticles, 
                             (Vector2){snake.positions[i].x + 10, snake.positions[i].y + 10},
                             (Color){0, 255, 0, 255}, 5);
            }
        }
    }
}

void DrawGame(void) {
    ClearBackground(BLACK);
    
    // Desenare fundal cu efect de gradient
    for(int y = 0; y < SCREEN_HEIGHT; y++) {
        float t = (float)y / SCREEN_HEIGHT;
        float wave = sinf(gameTime + t * 3) * 0.05f;
        Color color = ColorLerp(
            (Color){0, 0, 0, 255},
            (Color){0, 20, 0, 255},
            t + wave
        );
        DrawLine(0, y, SCREEN_WIDTH, y, color);
    }
    
    // Desenare particule în fundal
    DrawParticles(&foodParticles);
    
    // Desenare mâncare cu efect de pulsare
    float scale = 1.0f + sinf(gameTime * 4) * 0.1f;
    Color foodColor = (Color){255, 255, 0, (unsigned char)(200 + sinf(gameTime * 4) * 55)};
    DrawRectangle(food.position.x, food.position.y,
                 20 * scale, 20 * scale, foodColor);
    
    // Desenare șarpe
    DrawSnake(&snake);
    
    // Desenare particule pentru șarpe
    DrawParticles(&snakeParticles);
    
    // Desenare interfață
    DrawRectangle(10, 10, 200, 100, (Color){0, 0, 0, 150});
    DrawRectangleLines(10, 10, 200, 100, (Color){0, 255, 0, 100});
    
    char scoreText[32];
    sprintf(scoreText, "Scor: %d", score);
    DrawText(scoreText, 20, 20, 20, WHITE);
    
    char lengthText[32];
    sprintf(lengthText, "Lungime: %d", snake.length);
    DrawText(lengthText, 20, 50, 20, WHITE);
    
    char answersText[32];
    sprintf(answersText, "Corecte: %d", correctAnswers);
    DrawText(answersText, 20, 80, 20, WHITE);
    
    // Desenare întrebare dacă este activă
    if (IsQuestionActive()) {
        DrawQuestion();
    }
    
    // Desenare ecran game over
    if (gameOver) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 200});
        const char* gameOverText = "GAME OVER!";
        int textWidth = MeasureText(gameOverText, 60);
        DrawText(gameOverText,
                (SCREEN_WIDTH - textWidth) / 2,
                SCREEN_HEIGHT / 2 - 60,
                60, RED);
        
        char finalScoreText[64];
        sprintf(finalScoreText, "Scor final: %d", score);
        textWidth = MeasureText(finalScoreText, 30);
        DrawText(finalScoreText,
                (SCREEN_WIDTH - textWidth) / 2,
                SCREEN_HEIGHT / 2 + 20,
                30, WHITE);
        
        const char* restartText = "Apasa SPACE pentru a reîncepe";
        textWidth = MeasureText(restartText, 20);
        DrawText(restartText,
                (SCREEN_WIDTH - textWidth) / 2,
                SCREEN_HEIGHT / 2 + 60,
                20, GREEN);
    }
}

void ResumeGame(bool correctAnswer) {
    pauseGame = false;
    if (correctAnswer) {
        GrowSnake(&snake);
        SpawnFood(&food);
    } else {
        gameOver = true;
    }
}

// Adaugam o functie noua pentru curatarea resurselor la inchiderea jocului
void CleanupGame(void) {
    UnloadSnakeTextures(&snake);
}

bool IsGameOver(void) {
    return gameOver;
}

