#include "Physics.h"  // Assuming your header file is named Physics.h
#include <cmath>  // For math functions like pow, sqrt, atan, sin, cos

// Constructor (if you need to initialize some properties)
Physics::Physics() {
    // Initialization if necessary
}

// Implementing the time dilation method
double Physics::timeDilation(int hoursDay, int minutesHour) {
    return static_cast<double>(hoursDay) * minutesHour;
}

// Implementing the time per frame method
double Physics::timePerFrame(double td, int frameRate) {
    return td / frameRate;
}

// Implementing the rotation speed method
double Physics::rotationSpeed(int frameRate, double td, int secondsDay) {
    return -(2 * PI / frameRate) * (td / secondsDay);
}

// Implementing the gravity at an altitude method
double Physics::gravityAtAltitude(double g, double r, double h) {
    return g * pow((r / (r + h)), 2);
}

// Implementing the height above earth method
double Physics::heightAboveEarth(double x, double y, double r) {
    return sqrt(pow(x, 2) + pow(y, 2)) - r;
}

// Implementing the direction of gravity pull method
double Physics::directionOfGravity(double xe, double ye, double xs, double ys) {
    return atan2(ye - ys, xe - xs);  // atan2 returns values from -π to π, useful for directional angles
}

// Implementing the horizontal component of acceleration method
double Physics::horizontalAcceleration(double a, double angle) {
    return a * sin(angle);  // Assuming the angle is already in radians
}

// Implementing the vertical component of acceleration method
double Physics::verticalAcceleration(double a, double angle) {
    return a * cos(angle);  // Assuming the angle is already in radians
}

// Implementing Newton's first law for a position at a time t (you might want to pass t as a parameter)
double Physics::calculatePositionWithConstantVelocity(double s0, double v, double t) {
    return s0 + v * t;
}

// Methods for position calculation with constant velocity
double Physics::horizontalPositionConstantVelocity(double x0, double dx, double t) {
    return x0 + dx * t;
}

double Physics::verticalPositionConstantVelocity(double y0, double dy, double t) {
    return y0 + dy * t;
}

// Implementing the distance formula with acceleration
double Physics::calculatePosition(double s0, double v, double a, double t) {
    return s0 + v * t + 0.5 * a * pow(t, 2);
}

// Implementing the velocity with constant acceleration method
double Physics::velocityWithConstantAcceleration(double v0, double a, double t) {
    return v0 + a * t;
}

// Implementing the horizontal distance formula
double Physics::horizontalDistance(double x0, double dx, double ddx, double t) {
    return x0 + dx * t + 0.5 * ddx * pow(t, 2);
}

// Implementing the horizontal velocity with constant acceleration method
double Physics::horizontalVelocity(double dx0, double ddx, double t) {
    return dx0 + ddx * t;
}

// You would continue with similar implementations for any other methods you need.