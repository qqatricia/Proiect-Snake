#include "snake.h"
#include "config.h"
#include "utils.h"
#include "textures.h"
#include <stdio.h>
#include <math.h>

// Funcție helper pentru a menține poziția în limitele ecranului
static float WrapPosition(float pos, float max) {
    if (pos < 0) return max - 20;
    if (pos >= max) return 0;
    return pos;
}

static bool hasMoved = false;  // Flag pentru a urmări dacă șarpele s-a mișcat
static int moveCount = 0;      // Contor pentru numărul de mișcări

void InitSnake(Snake* snake) {
    printf("\n=== Initializing Snake ===\n");
    snake->length = 5;
    snake->dir = DIR_RIGHT;
    hasMoved = false;
    moveCount = 0;
    
    // Start snake in the middle of the screen
    int gridX = (SCREEN_WIDTH / 20) / 2;
    int gridY = (SCREEN_HEIGHT / 20) / 2;
    float startX = gridX * 20;
    float startY = gridY * 20;
    
    // Inițializează pozițiile segmentelor
    for (int i = 0; i < snake->length; i++) {
        snake->positions[i] = (Vector2){startX - (i * 20), startY};
        printf("Segment %d initialized at: (%.1f, %.1f)\n", i, snake->positions[i].x, snake->positions[i].y);
    }

    snake->headTexture = GenerateSnakeHeadTexture(snake->dir);
    snake->bodyTexture = GenerateSnakeBodyTexture();
    
    printf("=== Snake Initialization Complete ===\n\n");
}

void UpdateSnake(Snake* snake) {
    printf("\n--- Updating Snake Position ---\n");
    Vector2 oldHead = snake->positions[0];
    
    // Mută corpul
    for (int i = snake->length - 1; i > 0; i--) {
        snake->positions[i] = snake->positions[i - 1];
    }
    
    // Calculăm noua poziție a capului
    switch (snake->dir) {
        case DIR_UP:
            oldHead.y -= 20;
            break;
        case DIR_DOWN:
            oldHead.y += 20;
            break;
        case DIR_LEFT:
            oldHead.x -= 20;
            break;
        case DIR_RIGHT:
            oldHead.x += 20;
            break;
    }
    
    // Aplicăm wrap-around
    oldHead.x = WrapPosition(oldHead.x, SCREEN_WIDTH);
    oldHead.y = WrapPosition(oldHead.y, SCREEN_HEIGHT);
    
    // Actualizăm poziția capului
    snake->positions[0] = oldHead;
    
    // Actualizăm textura capului când se schimbă direcția
    static Direction lastDir = DIR_RIGHT;
    if (lastDir != snake->dir) {
        UnloadTexture(snake->headTexture);
        snake->headTexture = GenerateSnakeHeadTexture(snake->dir);
        lastDir = snake->dir;
    }
    
    hasMoved = true;
    moveCount++;
    
    printf("Snake head moved to: (%.1f, %.1f)\n", snake->positions[0].x, snake->positions[0].y);
    printf("Move count: %d\n", moveCount);
    printf("--- Snake Update Complete ---\n\n");
}

void DrawSnake(const Snake* snake) {
    const float OFFSET = 10.0f;  // Offset pentru centrare în pătrate
    
    // Desenează corpul șarpelui
    for (int i = snake->length - 1; i > 0; i--) {
        // Calculează unghiul de rotație pentru segmentul curent
        float rotation = 0.0f;
        if (i > 0) {
            Vector2 current = snake->positions[i];
            Vector2 next = snake->positions[i-1];
            rotation = atan2f(next.y - current.y, next.x - current.x) * RAD2DEG;
        }
        
        // Desenează segmentul de corp cu textură și rotație
        Rectangle source = (Rectangle){0, 0, 20, 20};
        Rectangle dest = (Rectangle){
            snake->positions[i].x + OFFSET,  // Adăugăm offset pentru centrare
            snake->positions[i].y + OFFSET,  // Adăugăm offset pentru centrare
            20, 20
        };
        DrawTexturePro(snake->bodyTexture, source, dest, (Vector2){10, 10}, rotation, WHITE);
    }
    
    // Desenează capul șarpelui
    Rectangle sourceHead = (Rectangle){0, 0, 20, 20};
    Rectangle destHead = (Rectangle){
        snake->positions[0].x + OFFSET,  // Adăugăm offset pentru centrare
        snake->positions[0].y + OFFSET,  // Adăugăm offset pentru centrare
        20, 20
    };
    float headRotation = 0.0f;
    switch(snake->dir) {
        case DIR_RIGHT: headRotation = 0.0f; break;
        case DIR_DOWN:  headRotation = 90.0f; break;
        case DIR_LEFT:  headRotation = 180.0f; break;
        case DIR_UP:    headRotation = 270.0f; break;
    }
    DrawTexturePro(snake->headTexture, sourceHead, destHead, (Vector2){10, 10}, headRotation, WHITE);
}

bool CheckCollisionWithWalls(const Snake* snake) {
    Vector2 head = snake->positions[0];
    return (head.x <= 0 || head.x >= SCREEN_WIDTH - 20 || head.y <= 0 || head.y >= SCREEN_HEIGHT - 20);
}

bool CheckCollisionWithSelf(const Snake* snake) {
    printf("\n--- Checking Snake Collision ---\n");
    printf("Has moved: %d, Move count: %d\n", hasMoved, moveCount);
    
    if (!hasMoved || moveCount < 3) {
        printf("Skipping collision check (grace period)\n");
        return false;
    }
    
    Vector2 head = snake->positions[0];
    printf("Head position: (%.1f, %.1f)\n", head.x, head.y);
    
    for (int i = 1; i < snake->length; i++) {
        printf("Checking segment %d at (%.1f, %.1f)\n", i, snake->positions[i].x, snake->positions[i].y);
        if (Vector2AreEqual(head, snake->positions[i])) {
            printf("Collision detected with segment %d!\n", i);
            return true;
        }
    }
    
    printf("No collision detected\n");
    printf("--- Collision Check Complete ---\n\n");
    return false;
}

void GrowSnake(Snake* snake) {
    if (snake->length < MAX_SNAKE_LENGTH) {
        snake->positions[snake->length] = snake->positions[snake->length - 1];
        snake->length++;
        printf("Snake grew! New length: %d\n", snake->length);
    }
}

void UnloadSnakeTextures(Snake* snake) {
    UnloadTexture(snake->headTexture);
    UnloadTexture(snake->bodyTexture);
}
