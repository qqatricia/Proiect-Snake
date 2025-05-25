#ifndef TEXTURES_H
#define TEXTURES_H

#include <raylib.h>
#include "snake.h"  // Pentru tipul Direction

// Generează o textură pentru capul șarpelui
Texture2D GenerateSnakeHeadTexture(Direction direction);

// Generează o textură pentru corpul șarpelui
Texture2D GenerateSnakeBodyTexture(void);

#endif // TEXTURES_H 