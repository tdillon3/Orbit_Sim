#include "position.h"
#include "velocity.h"

#pragma once
class Projectile
{
public:
   Projectile(Position pos, double angle) : pos(pos) 
   {
      dx = cos(angle) * 300000;
      dy = sin(angle) * 300000;
   }

   Position getPos()
   {
      return pos;
   }

   void update()
   {
      pos.addMetersX(dx);
      pos.addMetersY(dy);
   }

private:
   Position pos;
   double dx;
   double dy;
};

