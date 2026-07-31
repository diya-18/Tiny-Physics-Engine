#ifndef BODY_H
#define BODY_H

#include "vector.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float width;
    float height;
} Body;

#endif
