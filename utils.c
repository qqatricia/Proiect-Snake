#include "utils.h"
#include <math.h>

bool Vector2AreEqual(Vector2 a, Vector2 b) {
    // Convert to grid positions and compare
    int gridX1 = (int)(a.x / 20);
    int gridY1 = (int)(a.y / 20);
    int gridX2 = (int)(b.x / 20);
    int gridY2 = (int)(b.y / 20);
    return (gridX1 == gridX2) && (gridY1 == gridY2);
}
