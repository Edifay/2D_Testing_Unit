#include <simple2d.h>
#include <stdlib.h>
#include <time.h>
#include "entities/ball.h"
#include "logic/physic.h"

#define MAX_BALLS_COUNT 1000
// we will assume that the prog is always at 120hz.
#define FPS 120

S2D_Window* window;

Ball balls[MAX_BALLS_COUNT];
int ballNumber = 0;
int fps = FPS;

void on_key(S2D_Event e);

bool play = false;
bool fast = false;
bool jump = false;
bool spawn = false;

double lastFps = 0;

int repeated = 0;

void update() {
    if (lastFps != window->fps) {
        printf("Ball count : %d\n", ballNumber);
        printf("Current fps %lf\n", window->fps);
        lastFps = window->fps;
    }

    if (play) {
        for (int j = 0; j < 20; j++) {
            applyForce();
            applyVelocity();

            if (!spawn) {
                if (repeated == 10) {
                    balls[ballNumber].point = pointOf(150, 150);
                    balls[ballNumber].radius = 15;
                    balls[ballNumber].velocity.x = 6;
                    balls[ballNumber].velocity.y = 0;
                    ballNumber++;
                    repeated = 0;
                }

                repeated++;
            }
            if (!fast)
                break;
        }
    }

    if (jump) {
        for (int j = 0; j < 400; j++) {
            applyForce();
            applyVelocity();
            if (!spawn) {
                if (repeated == 10) {
                    balls[ballNumber].point = pointOf(150, 150);
                    balls[ballNumber].radius = 15;
                    balls[ballNumber].velocity.x = 6;
                    balls[ballNumber].velocity.y = 0;
                    ballNumber++;
                    repeated = 0;
                }

                repeated++;
            }
        }
        jump = !jump;
    }
}

void render() {
    for (int i = 0; i < ballNumber; i++) {
        drawBall(balls[i]);
    }
}


int main() {
    srand(time(NULL));

    window = S2D_CreateWindow(
        "Hello Triangle",
        1280,
        720,
        update,
        render,
        0
    );

    window->fps_cap = 120;
    window->vsync = false;
    window->on_key = on_key;


    S2D_Color background_color;
    background_color.a = 1;
    background_color.r = 1;
    background_color.b = 1;
    background_color.g = 1;
    window->background = background_color;

    S2D_Show(window);
    S2D_FreeWindow(window);
    return 0;
}


void on_key(S2D_Event e) {
    // Check `e.key` for the key being interacted with

    switch (e.type) {
        case S2D_KEY_DOWN:
            // printf("%s\n", e.key);

            if (strcmp("Space", e.key) == 0) {
                jump = !jump;
                break;
            }

            if (strcmp("S", e.key) == 0) {
                spawn = !spawn;
                break;
            }

            if (strcmp("P", e.key) == 0) {
                play = !play;
                break;
            }

            if (strcmp("F", e.key) == 0) {
                fast = !fast;
                break;
            }

            if (strcmp("R", e.key) == 0) {
                ballNumber = 0;
                repeated = 0;
                break;
            }

            if (ballNumber != MAX_BALLS_COUNT) {
                printf("Creating a ball at (%d, %d).\n", window->mouse.x, window->mouse.y);
                balls[ballNumber].point = pointOf(window->mouse.x, window->mouse.y);
                balls[ballNumber].radius = 60;
                balls[ballNumber].velocity.x = 6;
                balls[ballNumber].velocity.y = 0;
                ballNumber++;
            }

            break;

        case S2D_KEY_HELD:
            // Key is being held down
            break;

        case S2D_KEY_UP:
            // Key was released
            break;
    }
}
