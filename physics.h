/***********************************************************************
 * Header File:
 *    Physics : A class used to represent various physics calculations
 * Summary:
 *    Contains methods for various physics-related calculations for a
 *    simulated environment
 ************************************************************************/

#pragma once
#include <cmath> // For math operations
#include "position.h" // For position class
#include "velocity.h"  // For velocity class

// Constant for PI
const double PI = 3.14159265358979323846;

// Get gravity at given point
Acceleration getGravity(const Position& posElement);

// Update the current velocity
Velocity updateVelocity(Velocity& velocity, const Acceleration& acc, double t);

// update position
Position updatePosition(Position& pos, const Velocity& vel, const Acceleration& acc, double time);


// Helper method to calculate the power of values
double pow2(double value);


