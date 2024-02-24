#include "ball.h"

#include <simple2d.h>
#include <math.h>


Ball newBall(double x, double y, double radius) {
    Ball ball;
    ball.point = pointOf(x, y);
    ball.radius = radius;
    ball.velocity = vectorOf(0, 0);
    return ball;
}

Ball newBallP(Point point, double radius) {
    return newBall(point.x, point.y, radius);
}

void drawBall(Ball ball) {
    S2D_DrawCircle(ball.point.x, ball.point.y, ball.radius, M_PI * M_PI * log(ball.radius), 1, 0, 0, 1);
}
