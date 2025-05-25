#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>
#include <stddef.h>

#define MAX_PARTICLES 20

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float alpha;
    float lifetime;
    bool active;
} Particle;

typedef struct {
    Vector2 position;
    int points; // 1 sau 2
    float appearEffect;  // Pentru efectul de apariție/dispariție
} Food;

void InitFood(Food* food);
void SpawnFood(Food* food);
void DrawFood(const Food* food);
bool CheckFoodEaten(const Food* food, Vector2 snakeHead);
void MoveFood(Food* food);

#endif // FOOD_H
