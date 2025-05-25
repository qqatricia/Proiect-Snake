#include "particles.h"
#include <math.h>

void InitParticleSystem(ParticleSystem* system) {
    system->count = 100;
    for (int i = 0; i < system->count; i++) {
        system->particles[i].active = false;
    }
}

void EmitParticles(ParticleSystem* system, Vector2 position, Color color, int count) {
    for (int i = 0; i < system->count && count > 0; i++) {
        if (!system->particles[i].active) {
            system->particles[i].position = position;
            system->particles[i].velocity = (Vector2){
                (float)(GetRandomValue(-100, 100)) / 100.0f * 2.0f,
                (float)(GetRandomValue(-100, 100)) / 100.0f * 2.0f
            };
            system->particles[i].alpha = 1.0f;
            system->particles[i].color = color;
            system->particles[i].active = true;
            count--;
        }
    }
}

void UpdateParticles(ParticleSystem* system, float deltaTime) {
    for (int i = 0; i < system->count; i++) {
        if (system->particles[i].active) {
            system->particles[i].alpha -= deltaTime;
            if (system->particles[i].alpha <= 0) {
                system->particles[i].active = false;
                continue;
            }
            
            system->particles[i].position.x += system->particles[i].velocity.x * 60.0f * deltaTime;
            system->particles[i].position.y += system->particles[i].velocity.y * 60.0f * deltaTime;
            
            system->particles[i].color.a = (unsigned char)(255.0f * system->particles[i].alpha);
        }
    }
}

void DrawParticles(ParticleSystem* system) {
    for (int i = 0; i < system->count; i++) {
        if (system->particles[i].active) {
            DrawCircleV(system->particles[i].position, 2.0f, system->particles[i].color);
        }
    }
} 