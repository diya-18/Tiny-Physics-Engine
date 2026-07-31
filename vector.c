#include "vector.h"

Vector2 vec_add(Vector2 a, Vector2 b) {
    Vector2 r = { a.x + b.x, a.y + b.y };
    return r;
}

Vector2 vec_scale(Vector2 v, float s) {
    Vector2 r = { v.x * s, v.y * s };
    return r;
}
