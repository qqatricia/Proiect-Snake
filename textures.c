#include "textures.h"
#include "snake.h"
#include <math.h>

#define TEXTURE_SIZE 20

Texture2D GenerateSnakeHeadTexture(Direction direction) {
    Image img = GenImageColor(TEXTURE_SIZE, TEXTURE_SIZE, BLANK);
    
    // Desenează forma de bază a capului (oval)
    for(int y = 0; y < TEXTURE_SIZE; y++) {
        for(int x = 0; x < TEXTURE_SIZE; x++) {
            float centerX = TEXTURE_SIZE / 2.0f;
            float centerY = TEXTURE_SIZE / 2.0f;
            float dx = x - centerX;
            float dy = y - centerY;
            float distance = sqrtf(dx*dx + dy*dy);
            
            if(distance < TEXTURE_SIZE/2.0f) {
                ImageDrawPixel(&img, x, y, GREEN);
            }
        }
    }
    
    // Adaugă ochii în funcție de direcție
    Color eyeColor = WHITE;
    Color pupilColor = BLACK;
    int eyeSize = 4;
    int pupilSize = 2;
    
    switch(direction) {
        case DIR_RIGHT:
            ImageDrawCircle(&img, TEXTURE_SIZE-6, 6, eyeSize, eyeColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-6, TEXTURE_SIZE-6, eyeSize, eyeColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-5, 6, pupilSize, pupilColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-5, TEXTURE_SIZE-6, pupilSize, pupilColor);
            break;
        case DIR_LEFT:
            ImageDrawCircle(&img, 6, 6, eyeSize, eyeColor);
            ImageDrawCircle(&img, 6, TEXTURE_SIZE-6, eyeSize, eyeColor);
            ImageDrawCircle(&img, 5, 6, pupilSize, pupilColor);
            ImageDrawCircle(&img, 5, TEXTURE_SIZE-6, pupilSize, pupilColor);
            break;
        case DIR_UP:
            ImageDrawCircle(&img, 6, 6, eyeSize, eyeColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-6, 6, eyeSize, eyeColor);
            ImageDrawCircle(&img, 6, 5, pupilSize, pupilColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-6, 5, pupilSize, pupilColor);
            break;
        case DIR_DOWN:
            ImageDrawCircle(&img, 6, TEXTURE_SIZE-6, eyeSize, eyeColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-6, TEXTURE_SIZE-6, eyeSize, eyeColor);
            ImageDrawCircle(&img, 6, TEXTURE_SIZE-5, pupilSize, pupilColor);
            ImageDrawCircle(&img, TEXTURE_SIZE-6, TEXTURE_SIZE-5, pupilSize, pupilColor);
            break;
    }
    
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

Texture2D GenerateSnakeBodyTexture(void) {
    Image img = GenImageColor(TEXTURE_SIZE, TEXTURE_SIZE, BLANK);
    
    // Desenează forma de bază a segmentului (rotund)
    for(int y = 0; y < TEXTURE_SIZE; y++) {
        for(int x = 0; x < TEXTURE_SIZE; x++) {
            float centerX = TEXTURE_SIZE / 2.0f;
            float centerY = TEXTURE_SIZE / 2.0f;
            float dx = x - centerX;
            float dy = y - centerY;
            float distance = sqrtf(dx*dx + dy*dy);
            
            if(distance < TEXTURE_SIZE/2.0f - 1) {
                // Culoare de bază pentru corp
                Color baseColor = DARKGREEN;
                
                // Adaugă un model de solzi
                float scalePattern = sinf(x * 0.5f) * cosf(y * 0.5f);
                if(scalePattern > 0) {
                    baseColor.r += 20;
                    baseColor.g += 20;
                    baseColor.b += 20;
                }
                
                ImageDrawPixel(&img, x, y, baseColor);
            }
        }
    }
    
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
} 