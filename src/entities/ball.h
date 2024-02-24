#ifndef BALL_H
#define BALL_H

#include "../maths/geo2D.h"

typedef struct {
    Point point;
    double radius;
    Vector velocity;
} Ball;


Ball newBall(double x, double y, double radius);

Ball newBallP(Point point, double radius);

void drawBall(Ball ball);

#endif //BALL_H
