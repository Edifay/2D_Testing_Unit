#include "geo2D.h"

#include <math.h>
#include <stdio.h>


Vector vectorOf(double x, double y) {
    Vector vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

Point pointOf(double x, double y) {
    Point point;
    point.x = x;
    point.y = y;
    return point;
}


/*
 * A vector going from a to b.
 */
Vector createVector(Point a, Point b) {
    return vectorOf(b.x - a.x, b.y - a.y);
}

/*
 * Sum of 2 points.
 */
Point sumPoint(Point a, Point b) {
    return pointOf(a.x + b.x, a.y + b.y);
}

/*
 * Sum of 2 vectors.
 */
Vector sumVector(Vector a, Vector b) {
    return vectorOf(a.x + b.x, a.y + b.y);
}

/*
 * Returning scalaire of a and b.
 */
double scalaire(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

Point multPoint(Point a, double value) {
    return pointOf(value * a.x, value * a.y);
}

Vector multVector(Vector a, double value) {
    return vectorOf(value * a.x, value * a.y);
}

double norm(Vector vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

double distance(Point a, Point b) {
    return norm(createVector(a, b));
}


void printVector(Vector vec) {
    printf("Vect (%lf, %lf)", vec.x, vec.y);
}

void printPoint(Point point) {
    printf("Point (%lf, %lf)", point.x, point.y);
}


Vector oppositeVector(Vector vect) {
    return vectorOf(-vect.x, -vect.y);
}

Point oppositePoint(Point point) {
    return pointOf(-point.x, -point.y);
}


Vector vectOfPoint(Point p) {
    return vectorOf(p.x, p.y);
}

Point pointOfVect(Vector vect) {
    return pointOf(vect.x, vect.y);
}

Segment segmentOf(Point a, Point b) {
    Segment newSegment;
    newSegment.a = a;
    newSegment.b = b;
    return newSegment;
}

Vector vectorFromSegment(Segment segment) {
    return createVector(segment.a, segment.b);
}

double vectorAngle(Vector vector) {
    Point adjacent = pointOf(vector.x, 0);
    double adjacentLength = distance(pointOf(0, 0), adjacent);
    double hypothenuseLength = distance(pointOf(0, 0), pointOfVect(vector));
    if (hypothenuseLength == 0)
        return 0;
    return acos(adjacentLength / hypothenuseLength);
}


Point rotatePoint(Point point, Point origin, double angle) {
    return pointOf(
        origin.x + (point.x - origin.x) * cos(angle) - (point.y - origin.y) * sin(angle),
        origin.y + (point.x - origin.x) * sin(angle) + (point.y - origin.y) * cos(angle)
    );
}

double distancePointSegment(Point point, Segment segment) {
    double angle = -vectorAngle(vectorFromSegment(segment));
    Point origin = segment.a;

    Segment rotatedSegment = segmentOf(segment.a, rotatePoint(segment.b, origin, angle));
    Point rotatedPoint = rotatePoint(point, origin, angle);
    Point projected = pointOf(rotatedPoint.x, segment.a.y);

    if (rotatedSegment.a.x > projected.x) {
        projected.x = rotatedSegment.a.x;
    }
    else if (rotatedSegment.b.x < projected.x) {
        projected.x = rotatedSegment.b.x;
    }

    return distance(rotatedPoint, projected);
}


Point pointCopy(Point point) {
    return pointOf(point.x, point.y);
}

Vector vectorCopy(Vector vector) {
    return vectorOf(vector.x, vector.y);
}
