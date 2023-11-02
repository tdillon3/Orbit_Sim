/***************************
* Header file for direction class
***************************/

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#endif // M_PI

inline double degreesFromRadians(double radians) 
{ 
   return radians * 180.0 / M_PI; 
}

inline double radiansFromDegrees(double degrees)
{
   return degrees * M_PI / 180.0; 
}

class Direction
{
public:
   Direction() : radians(0.0) {}
   Direction(double degrees) : radians(radiansFromDegrees(degrees)) {}
   Direction(const Direction& rhs) : radians(rhs.radians) {}
   Direction& operator = (const Direction& rhs)
   {
      radians = rhs.radians;
      return *this;
   }

   // setters. Keep radians between -PT to PI
   void setRadians(double rhs)
   {
      if (rhs >= 0.0) 
      {
         double rotations = (double)(int)((M_PI + rhs) / (2.0 * M_PI));
         rhs -= rotations * 2.0 * M_PI;
      }
      else 
      {
         double rotations = (double)(int)((M_PI - rhs) / (2.0 * M_PI));
         rhs += rotations * 2.0 * M_PI;
      }
   }
   void setDegrees(double rhs) { radians = radiansFromDegrees(rhs); }

   // set based on the components
   void setDxDy(double dx, double dy)
   {
      radians = atan2(dx, dy);
   }

   void setDown() { radians = M_PI; }
   void setUp() { radians = 0.0; }
   void setRight() { radians = M_PI_2; }
   void setLeft() { radians = -M_PI_2; }
   void reverse() { radians += M_PI; }

   // rotate by an amount in radians 
   void rotate(double amount) 
   {
      radians += amount;
      if (radians > M_PI)
         radians -= 2.0 * M_PI;
      else if (radians < -M_PI)
         radians += 2.0 * M_PI;
   }

   // getters
   double getRadians() const { return radians; }
   double getDegrees() const { return degreesFromRadians(radians); }

   double getDx() const { return sin(radians); }
   double getDy() const { return cos(radians); }

   bool isRight() const { return radians > 0.0 && radians < M_PI; }
   bool isLeft() const { return radians < 0.0 && radians > -M_PI; }

   Direction operator+(double degrees) const { return Direction(getDegrees() + degrees); }
   Direction operator+(Direction rhs) const 
   {
      rhs.rotate(radians);
      return rhs;
   }

private:
  
   double radians;
};


