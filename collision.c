#include "collision.h"

int aabb_overlap(Body *a, Body *b)
{
    if (a->position.x + a->width  < b->position.x) return 0;
    if (a->position.x > b->position.x + b->width) return 0;
    if (a->position.y + a->height < b->position.y) return 0;
    if (a->position.y > b->position.y + b->height) return 0;
    return 1;
}
