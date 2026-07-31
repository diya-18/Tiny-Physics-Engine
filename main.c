#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "body.h"
#include "collision.h"

#define BODY_COUNT 3
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Physics Engine (SDL2)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // BODIES
    Body bodies[BODY_COUNT] = {
        { {200, 100}, { 100, 0}, {0, 800}, 30, 30 },
        { {350, 100}, {-100, 0}, {0, 800}, 30, 30 },
        { {500, 100}, {   0, 0}, {0, 800}, 30, 30 }
    };

    Uint64 last_ticks = SDL_GetTicks64();
    SDL_Event event;
    int running = 1;

    while (running) {

        // EVENTS
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // TIME
        Uint64 current_ticks = SDL_GetTicks64();
        float dt = (current_ticks - last_ticks) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        last_ticks = current_ticks;

        // PHASE 1: PHYSICS INTEGRATION
          
        for (int i = 0; i < BODY_COUNT; i++) {

            bodies[i].velocity =
                vec_add(bodies[i].velocity,
                        vec_scale(bodies[i].acceleration, dt));

            bodies[i].position =
                vec_add(bodies[i].position,
                        vec_scale(bodies[i].velocity, dt));

            float ground = WINDOW_HEIGHT - bodies[i].height;

            if (bodies[i].position.y > ground) {
                bodies[i].position.y = ground;

                float restitution = 0.6f;
                bodies[i].velocity.y = -bodies[i].velocity.y * restitution;

                float friction = 0.8f;
                bodies[i].velocity.x *= friction;

                if (fabs(bodies[i].velocity.x) < 5.0f)
                    bodies[i].velocity.x = 0.0f;
            }

            if (bodies[i].position.x < 0 ||
                bodies[i].position.x + bodies[i].width > WINDOW_WIDTH) {
                bodies[i].velocity.x = -bodies[i].velocity.x;
            }
        }

        // PHASE 2: BODY–BODY COLLISIONS
        for (int i = 0; i < BODY_COUNT; i++) {
            for (int j = i + 1; j < BODY_COUNT; j++) {

                if (aabb_overlap(&bodies[i], &bodies[j])) {

                    float overlap =
                        (bodies[i].position.x + bodies[i].width)
                        - bodies[j].position.x;

                    bodies[i].position.x -= overlap * 0.5f;
                    bodies[j].position.x += overlap * 0.5f;

                    float temp = bodies[i].velocity.x;
                    bodies[i].velocity.x = bodies[j].velocity.x;
                    bodies[j].velocity.x = temp;
                }
            }
        }

        // PHASE 3: RENDER
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < BODY_COUNT; i++) {
            SDL_Rect box = {
                (int)bodies[i].position.x,
                (int)bodies[i].position.y,
                (int)bodies[i].width,
                (int)bodies[i].height
            };

            SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
            SDL_RenderFillRect(renderer, &box);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
