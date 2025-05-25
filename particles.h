#ifndef PARTICLES_H
#define PARTICLES_H

#include <raylib.h>
#include "food.h"

typedef struct {
    Particle particles[100];
    int count;
} ParticleSystem;

void InitParticleSystem(ParticleSystem* system);
void EmitParticles(ParticleSystem* system, Vector2 position, Color color, int count);
void UpdateParticles(ParticleSystem* system, float deltaTime);
void DrawParticles(ParticleSystem* system);

#endif // PARTICLES_H 