#include "food.h"
#include "config.h"
#include <raylib.h>
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

static float pulseTime = 0.0f;
static Particle particles[MAX_PARTICLES];

void InitFood(Food* food) {
    srand(time(NULL));
    MoveFood(food);
    
    // Inițializează particulele
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].active = false;
    }
}

// SpawnFood este un alias pentru MoveFood pentru compatibilitate
void SpawnFood(Food* food) {
    MoveFood(food);
}

void MoveFood(Food* food) {
    // Asigură-te că mâncarea apare pe grid
    int gridWidth = SCREEN_WIDTH / 20;
    int gridHeight = SCREEN_HEIGHT / 20;
    
    food->position.x = GetRandomValue(0, gridWidth - 1) * 20;
    food->position.y = GetRandomValue(0, gridHeight - 1) * 20;
    
    // Inițializează efectul de apariție
    food->appearEffect = 1.0f;
    
    food->points = (rand() % 2) + 1; // 1 sau 2 puncte
    
    printf("\nMâncare nouă generată la poziția grid (%d, %d) -> pixeli (%.0f, %.0f)\n", 
           food->position.x / 20, food->position.y / 20, food->position.x, food->position.y);
    
    // Activează particule noi
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position = food->position;
        particles[i].velocity = (Vector2){
            (float)(rand() % 100 - 50) / 100.0f,
            (float)(rand() % 100 - 50) / 100.0f
        };
        particles[i].color = food->points == 2 ? RED : GOLD;
        particles[i].alpha = 1.0f;
        particles[i].active = true;
    }
    
    // Adăugăm verificare suplimentară
    if (food->position.x < 20 || food->position.x > SCREEN_WIDTH - 40 ||
        food->position.y < 20 || food->position.y > SCREEN_HEIGHT - 40) {
        printf("\nWARNING: Food spawned too close to border! Respawning...\n");
        MoveFood(food);  // Reîncercăm dacă poziția nu este bună
        return;
    }
}

void UpdateFoodEffects(void) {
    pulseTime += GetFrameTime() * 2.0f;
    
    // Actualizează particulele
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].position.x += particles[i].velocity.x;
            particles[i].position.y += particles[i].velocity.y;
            particles[i].alpha -= 0.01f;
            
            if (particles[i].alpha <= 0) {
                particles[i].active = false;
            }
        }
    }
}

void DrawFood(const Food* food) {
    // Calculăm centrul celulei
    Vector2 center = {
        food->position.x + 10,
        food->position.y + 10
    };
    
    // Desenăm mărul
    Color appleColor = food->points == 2 ? RED : MAROON;
    
    // Corpul mărului (cerc)
    DrawCircleV(center, 8, appleColor);
    
    // Codița mărului (dreptunghi maro)
    DrawRectangle(center.x - 1, center.y - 9, 2, 4, BROWN);
    
    // Frunza (triunghi verde)
    Vector2 leaf[3] = {
        {center.x + 2, center.y - 8},
        {center.x + 6, center.y - 10},
        {center.x + 2, center.y - 12}
    };
    DrawTriangle(leaf[0], leaf[1], leaf[2], DARKGREEN);
    
    // Adăugăm un mic efect de strălucire
    DrawCircle(center.x - 3, center.y - 3, 2, (Color){255, 255, 255, 100});
}

bool CheckFoodEaten(const Food* food, Vector2 snakeHead) {
    // Verifică dacă pozițiile sunt pe aceeași celulă din grilă
    int foodGridX = (int)(food->position.x / 20);
    int foodGridY = (int)(food->position.y / 20);
    int snakeGridX = (int)(snakeHead.x / 20);
    int snakeGridY = (int)(snakeHead.y / 20);
    
    printf("Checking grid positions - Food: (%d, %d), Snake: (%d, %d)\n",
           foodGridX, foodGridY, snakeGridX, snakeGridY);
           
    bool collision = (foodGridX == snakeGridX) && (foodGridY == snakeGridY);
    
    if (collision) {
        printf("COLLISION DETECTED on grid position (%d, %d)!\n", foodGridX, foodGridY);
    }
    
    return collision;
}
