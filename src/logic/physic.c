#include "physic.h"
#include <simple2d.h>
#include "../entities/ball.h"
#include "../global.h"

#define GRAVITY_VALUE 9.81
#define REACTION_COEFF 1.2
#define AIR_FRICTION_COEFF 0.999
#define VELOCITY_COEFF 1.0

void applyVectorOnVector(Vector* vect1, Vector vect2) {
    vect1->x += vect2.x;
    vect1->y += vect2.y;
}


void applyForce() {
    double tickValue = 1.0 / fps;

    // gravity
    Vector gravity = vectorOf(0, GRAVITY_VALUE);
    Vector tickedGravity = multVector(gravity, tickValue);
    for (int i = 0; i < ballNumber; i++) {
        applyVectorOnVector(&balls[i].velocity, tickedGravity);
    }

    // reaction
    for (int i = 0; i < ballNumber; i++) {
        Ball* ball = balls + i;
        Ball* second;
        for (int j = i + 1; j < ballNumber; j++) {
            if (i == j)
                continue;
            second = balls + j;
            double dist;
            if ((dist = distance(ball->point, second->point)) < ball->radius + second->radius) {
                applyVectorOnVector(&balls[i].velocity, multVector(tickedGravity, -1));

                // printf("touch %d %d\n", i, j);


                Segment seg = segmentOf(ball->point, second->point);
                Vector vectSeg = vectorFromSegment(seg);

                if (dist < 0.01) {
                    dist = 0.01;
                    vectSeg = vectorOf(0, 1);
                }

                double rapport = (ball->radius + second->radius - dist) / dist * 0.6;


                if (rapport < 0.01) {
                    rapport = 0.01;
                }

                if (rapport > 1)
                    rapport = 1;

                // printf("Rapport : %lf\n", rapport);

                // applyVectorOnVector(&second->velocity, multVector(vectSeg, rapport));
                // applyVectorOnVector(&ball->velocity, multVector(vectSeg, -rapport));

                double ratio = second->radius / ball->radius;

                applyVectorOnVector(&second->velocity, multVector(vectSeg, (1/ratio) * rapport));
                applyVectorOnVector(&ball->velocity, multVector(vectSeg, -rapport * ( ratio)));
                applyVectorOnVector(&ball->velocity, multVector(vectorOf(ball->velocity.x, ball->velocity.y), -0.005));
            }
        }

        // printf("Ball y %lf\n", ball->point.y);
        if (ball->point.y + ball->radius > 700) {
            ball->velocity.y = 0;
            applyVectorOnVector(&ball->velocity,
                                multVector(vectorOf(0, (ball->point.y + ball->radius - 700) / ball->radius),
                                           -5));
            applyVectorOnVector(&ball->velocity, multVector(vectorOf(ball->velocity.x, ball->velocity.y), -0.005));
        }

        // printf("Ball x :%lf", ball->point.x);

        if (ball->point.x + ball->radius < 100) {
            ball->velocity.x = -ball->velocity.x * 0.2;
            ball->point.x = 100 - ball->radius;
        }

        if (ball->point.x + ball->radius > 1000) {
            ball->velocity.x = -ball->velocity.x * 0.2;
            ball->point.x = 1000 - ball->radius;
        }
    }


    // friction
    for (int i = 0; i < ballNumber; i++) {
        Ball* ball = balls + i;

        ball->velocity.x *= AIR_FRICTION_COEFF;
        ball->velocity.y *= AIR_FRICTION_COEFF;
    }
}

void applyVelocity() {
    for (int i = 0; i < ballNumber; i++) {
        balls[i].point.x += balls[i].velocity.x * VELOCITY_COEFF;
        balls[i].point.y += balls[i].velocity.y * VELOCITY_COEFF;
    }
}
