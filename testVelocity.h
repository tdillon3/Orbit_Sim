#include <iostream>
#include <cmath>
#include <cassert>
#include "direction.h"
#include "velocity.h"
#pragma once

class TestVelocity
{
public:

   void testDefaultConstructor() {
      Velocity v;
      assert(v.getDx() == 0.0);
      assert(v.getDy() == 0.0);
      assert(v.getSpeed() == 0.0);
   }

   void testParameterizedConstructor() {
      Velocity v(2.5, 3.5);
      assert(v.getDx() == 2.5);
      assert(v.getDy() == 3.5);
      assert(fabs(v.getSpeed() - 4.30116) < 1e-5);  
   }

   void testCopyConstructor() {
      Velocity original(1.0, 2.0);
      Velocity copy(original);
      assert(copy.getDx() == original.getDx());
      assert(copy.getDy() == original.getDy());
      assert(fabs(copy.getSpeed() - original.getSpeed()) < 1e-5);
   }

   void testSetSpeedDirection() {
      Velocity v;
      v.setSpeedDirection(3.0, Direction(45)); 
      double x = v.getDx() - 3.0 * cos(PI / 4.0);
      assert(fabs(v.getDx() - 3.0 * cos(PI / 4.0)) < 1e-5);
      assert(fabs(v.getDy() - 3.0 * sin(PI / 4.0)) < 1e-5);
      assert(fabs(v.getSpeed() - 3.0) < 1e-5);
   }

   void testReverse() {
      Velocity v(2.0, 3.0);
      v.reverse();
      assert(v.getDx() == -2.0);
      assert(v.getDy() == -3.0);
      assert(fabs(v.getSpeed() - 3.60555) < 1e-5);  
   }

   void run() {

      testDefaultConstructor();
      testParameterizedConstructor();
      testCopyConstructor();
      testSetSpeedDirection();
      testReverse(); 

      std::cout << "All velocity tests passed!" << std::endl;
   }

};

