/***********************************************************************
 * Header File:
 *    Physics : A class used to represent various physics calculations
 * Summary:
 *    Contains methods for various physics-related calculations for a
 *    simulated environment, such as time dilation, rotation, gravity, etc.
 ************************************************************************/

#pragma once
#include <cmath> // For math operations

 // Constant for PI
const double PI = 3.14159265358979323846;

class Physics
{
public:
    Physics();  // default constructor if needed

    // Time-related calculations
    double timeDilation(int hoursDay, int minutesHour);
    double timePerFrame(double td, int frameRate);
    double rotationSpeed(int frameRate, double td, int secondsDay);

    // Gravity-related calculations
    double gravityAtAltitude(double g, double r, double h);
    double heightAboveEarth(double x, double y, double r);
    double directionOfGravity(double xe, double ye, double xs, double ys);
    double horizontalAcceleration(double a, double angle);
    double verticalAcceleration(double a, double angle);

    // Motion calculations based on Newton's laws
    double calculatePositionWithConstantVelocity(double s0, double v, double t);
    double horizontalPositionConstantVelocity(double x0, double dx, double t);
    double verticalPositionConstantVelocity(double y0, double dy, double t);
    double calculatePosition(double s0, double v, double a, double t);
    double velocityWithConstantAcceleration(double v0, double a, double t);
    double horizontalDistance(double x0, double dx, double ddx, double t);
    double horizontalVelocity(double dx0, double ddx, double t);

private:
    // Helper method to calculate the power of values
    double pow2(double value);

    // Add any other private methods or member variables as needed
};
