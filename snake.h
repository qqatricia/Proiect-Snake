#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>
#include <stddef.h>

#define MAX_SNAKE_LENGTH 100

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct {
    Vector2 positions[MAX_SNAKE_LENGTH];
    int length;
    Direction dir;
    Texture2D headTexture;    // Textura pentru capul șarpelui
    Texture2D bodyTexture;    // Textura pentru corpul șarpelui
} Snake;

void InitSnake(Snake* snake);
void UpdateSnake(Snake* snake);
void DrawSnake(const Snake* snake);
bool CheckCollisionWithWalls(const Snake* snake);
bool CheckCollisionWithSelf(const Snake* snake);
void GrowSnake(Snake* snake);
void UnloadSnakeTextures(Snake* snake);  // Funcție nouă pentru descărcarea texturilor

#endif // SNAKE_H
