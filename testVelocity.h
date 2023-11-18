#include <iostream>
#include <cmath>
#include <cassert>
#include "direction.h"
#include "velocity.h"
#pragma once

/*******************************
 * TEST Velocity
 * A friend class for Velocity which contains the Velocity unit tests
 ********************************/
class TestVelocity
{
public:
    void run()
    {
        testDefaultConstructor();
        testParameterizedConstructor();
        testCopyConstructor();
        testSetSpeedDirection();
        testReverse();

        std::cout << "All velocity tests passed!" << std::endl;
    }

private:
    // utility function for comparing floating point numbers
    bool closeEnough(double value, double test, double tolerance) const
    {
        double difference = value - test;
        return (difference >= -tolerance) && (difference <= tolerance);
    }

    void testDefaultConstructor() const
    {  // setup
       // exercise
        Velocity v;
        // verify
        assert(v.getDx() == 0.0);
        assert(v.getDy() == 0.0);
        assert(v.getSpeed() == 0.0);
    }  // teardown

    void testParameterizedConstructor() const
    {  // setup
       // exercise
        Velocity v(2.5, 3.5);
        // verify
        assert(v.getDx() == 2.5);
        assert(v.getDy() == 3.5);
        assert(closeEnough(v.getSpeed(), 4.30116, 1e-5));
    }  // teardown

    void testCopyConstructor() const
    {  // setup
        Velocity original(1.0, 2.0);
        // exercise
        Velocity copy(original);
        // verify
        assert(copy.getDx() == original.getDx());
        assert(copy.getDy() == original.getDy());
        assert(closeEnough(copy.getSpeed(), original.getSpeed(), 1e-5));
    }  // teardown

    void testSetSpeedDirection() const
    {  // setup
        Velocity v;
        // exercise
        v.setSpeedDirection(3.0, Direction(45));
        // verify
        assert(closeEnough(v.getDx(), 3.0 * cos(PI / 4.0), 1e-5));
        assert(closeEnough(v.getDy(), 3.0 * sin(PI / 4.0), 1e-5));
        assert(closeEnough(v.getSpeed(), 3.0, 1e-5));
    }  // teardown

    void testReverse() const
    {  // setup
        Velocity v(2.0, 3.0);
        // exercise
        v.reverse();
        // verify
        assert(v.getDx() == -2.0);
        assert(v.getDy() == -3.0);
        assert(closeEnough(v.getSpeed(), 3.60555, 1e-5));
    }  // teardown
};
