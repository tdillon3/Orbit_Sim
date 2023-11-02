#include "velocity.h"

#define _USE_MATH_DEFINES
#include <cmath>

/***************************
* Velocity :: GET DIRECTION
***************************/
Direction Velocity::getDirection() const
{
   Direction d;
   d.setDxDy(dx, dy);
   return d;
}

/***************************
* Velocity :: SET SpeedDirection
***************************/
void Velocity::setSpeedDirection(double speed, const Direction& direction)
{
   dx = speed * cos(direction.getRadians());
   dy = speed * sin(direction.getRadians());
}

/********************************
* Velocity :: setAccDirection
*******************************/
void Acceleration::setAccDirection(double acc, const Direction& direction)
{
   ddx = acc * direction.getDx();
   ddy = acc * direction.getDy();
}

/********************************
* Velocity :: Display
********************************/
std::ostream& operator << (std::ostream& out, const Velocity& v)
{
   out << "[" << v.getDx() << ", " << v.getDy() << "]";
   return out;
}