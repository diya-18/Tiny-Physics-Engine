#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} Vector2;

Vector2 vec_add(Vector2 a, Vector2 b);
Vector2 vec_scale(Vector2 v, float s);

#endif
