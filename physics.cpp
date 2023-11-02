#include "Physics.h"  // Assuming your header file is named Physics.h
#include <cmath>  // For math functions like pow, sqrt, atan, sin, cos


const double earthRadius = 6371000.0;  // meters

// Get altitude from position
double getAltitude(const Position& pos)
{
   double distance = computeDistance(Position(), pos);
   return distance - earthRadius;
}

// Get gravity at given point
Acceleration getGravity(const Position& posElement)
{
   double altitude = getAltitude(posElement);

   Direction direction;
   direction.setDxDy(-posElement.getMetersX(), -posElement.getMetersY());
   
   double standardGravity = 9.806;
   double tmp = earthRadius / (earthRadius + altitude);
   double acceleration = standardGravity * tmp * tmp;
   
   return Acceleration(acceleration, direction);
}

// Update the current velocity
Velocity updateVelocity(Velocity& velocity, const Acceleration& acc, double t)
{
   velocity.addDx(acc.getDdx() * t);
   velocity.addDy(acc.getDdy() * t);
   return velocity;
}

// Update the current position
Position updatePosition(Position& pos, const Velocity& vel, const Acceleration& acc, double t)
{
   pos.addMetersX(vel.getDx() * t + 0.5 * acc.getDdx() * t * t);
   pos.addMetersY(vel.getDy() * t + 0.5 * acc.getDdy() * t * t);
   return pos;
}

