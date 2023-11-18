#include <iostream>
#include <cmath>
#include <cassert>
#include "direction.h"
#pragma once
class TestDirection
{
public: 

   const double EPSILON = 1e-5; 

   void testDefaultConstructor() {
      Direction d;
      assert(fabs(d.getRadians() - 0.0) < EPSILON);
      assert(fabs(d.getDegrees() - 0.0) < EPSILON);
   }

   void testParameterizedConstructor() {
      Direction d(45.0);
      assert(fabs(d.getRadians() - (M_PI / 4.0)) < EPSILON);
      assert(fabs(d.getDegrees() - 45.0) < EPSILON);
   }

   void testCopyConstructor() {
      Direction original(30.0);
      Direction copy(original);
      assert(fabs(copy.getRadians() - original.getRadians()) < EPSILON);
      assert(fabs(copy.getDegrees() - original.getDegrees()) < EPSILON);
   }

   void testSetRadians() {
      Direction d;
      d.setRadians(3.0);
      double x = d.getRadians() - 3.0;
      assert(fabs(d.getRadians() - 3.0) < EPSILON);

      d.setRadians(2.0 * M_PI + 1.0);
      assert(fabs(d.getRadians() - 1.0) < EPSILON);

      d.setRadians(-3.0);
      assert(fabs(d.getRadians() - (-3.0)) < EPSILON);

      d.setRadians(-2.0 * M_PI - 1.0);
      assert(fabs(d.getRadians() - (-1.0)) < EPSILON);
   }

   void testSetDegrees() {
      Direction d;
      d.setDegrees(90.0);
      assert(fabs(d.getRadians() - (M_PI / 2.0)) < EPSILON);

      d.setDegrees(180.0);
      assert(fabs(d.getRadians() + M_PI) < EPSILON);

      d.setDegrees(360.0);
      assert(fabs(d.getRadians() - 0.0) < EPSILON);

      d.setDegrees(-90.0);
      assert(fabs(d.getRadians() - (-M_PI / 2.0)) < EPSILON);
   }

   void run() {
      testDefaultConstructor();
      testParameterizedConstructor();
      testCopyConstructor();
      testSetRadians();
      testSetDegrees();

      std::cout << "All direction tests passed!" << std::endl;
   }

};

