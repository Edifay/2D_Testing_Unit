#ifndef GEO2D_H
#define GEO2D_H

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double x;
    double y;
} Vector;

typedef struct {
    Point a;
    Point b;
} Segment;

Vector vectorOf(double x, double y);

Point pointOf(double x, double y);

/*
 * A vector going from a to b.
 */
Vector createVector(Point a, Point b);

/*
 * Sum of 2 points.
 */
Point sumPoint(Point a, Point b);

/*
 * Sum of 2 vectors.
 */
Vector sumVector(Vector a, Vector b);

/*
 * Returning scalaire of a and b.
 */
double scalaire(Vector a, Vector b);

Point multPoint(Point a, double value);

Vector multVector(Vector a, double value);

double norm(Vector vector);

double distance(Point a, Point b);

void printVector(Vector vec);

void printPoint(Point point);

Vector oppositeVector(Vector vect);

Point oppositePoint(Point point);

Vector vectOfPoint(Point p);

Point pointOfVect(Vector vect);

Segment segmentOf(Point a, Point b);

Vector vectorFromSegment(Segment segment);

double vectorAngle(Vector vector);

double distancePointSegment(Point point, Segment segment);

Point pointCopy(Point point);

Vector vectorCopy(Vector vector);

#endif //GEO2D_H
