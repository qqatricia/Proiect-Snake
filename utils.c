#include "utils.h"
#include <math.h>

bool Vector2Equals(Vector2 a, Vector2 b) {
    const float EPSILON = 0.001f;
    return (fabs(a.x - b.x) < EPSILON) && (fabs(a.y - b.y) < EPSILON);
}
