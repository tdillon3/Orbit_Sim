#pragma once

#include <ostream>
#include "direction.h"

/***************************************
* VELOCITY
* speec in meters per second
***************************************/
class Velocity
{
public:
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}
   Velocity(const Velocity& rhs) : dx(rhs.dx), dy(rhs.dy) {}
   Velocity(double speed, const Direction& direction) : dx(0.0), dy(0.0)
   {
      setSpeedDirection(speed, direction);
   }
   Velocity& operator = (const Velocity& rhs)
   {
      dx = rhs.dx;
      dy = rhs.dy;
      return *this;
   }

   // getters
   double getDx() const { return dx; }
   double getDy() const { return dy; }
   double getSpeed() const { return sqrt(dx * dx + dy * dy); }
   Direction getDirection() const;

   // setters
   void setDx(double dx) { this->dx = dx; }
   void setDy(double dy) { this->dy = dy; }
   void setDxDy(double dx, double dy) { this->dx = dx; this->dy = dy; }
   void setSpeed(double speed) { setSpeedDirection(speed, getDirection()); }
   void setDirection(const Direction& direction) { setSpeedDirection(getSpeed(), direction); }
   void setSpeedDirection(double speed, const Direction& direction);

   void addDx(double dx) { this->dx += dx; }
   void addDy(double dy) { this->dy += dy; }
   void addV(const Velocity& v) { dx += v.dx; dy += v.dy; }
   Velocity& operator += (const Velocity& rhs)
   {
      addV(rhs);
      return *this;
   }
   void reverse() { dx = -dx; dy = -dy; }

private:
   double dx;
   double dy;
};

std::ostream& operator << (std::ostream& out, const Velocity& v);

class Acceleration
{
public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double acc, const Direction& direction) : ddx(0.0), ddy(0.0)
   {
      setAccDirection(acc, direction);
   }
   Velocity getVelocity(double time) const { return Velocity(ddx * time, ddy * time); }

   double getDdx() const { return ddx; }
   double getDdy() const { return ddy; }

   void setAccDirection(double acc, const Direction& direction);

private:
   double ddx;
   double ddy;
};
