#include <iostream>
#include <cmath>
#include <cassert>
#include "direction.h"
#pragma once


/*******************************
 * TEST Direction
 * A friend class for Direction which contains the Direction unit tests
 ********************************/
class TestDirection
{
public:
    void run()
    {
        testDefaultConstructor();
        testParameterizedConstructor();
        testCopyConstructor();
        testSetRadians();
        testSetDegrees();

        std::cout << "All direction tests passed!" << std::endl;
    }

private:
    const double EPSILON = 1e-5;

    // utility function for comparing floating point numbers
    bool closeEnough(double value, double test) const
    {
        return fabs(value - test) < EPSILON;
    }

    void testDefaultConstructor() const
    {  // setup
       // exercise
        Direction d;
        // verify
        assert(closeEnough(d.getRadians(), 0.0));
        assert(closeEnough(d.getDegrees(), 0.0));
    }  // teardown

    void testParameterizedConstructor() const
    {  // setup
       // exercise
        Direction d(45.0);
        // verify
        assert(closeEnough(d.getRadians(), M_PI / 4.0));
        assert(closeEnough(d.getDegrees(), 45.0));
    }  // teardown

    void testCopyConstructor() const
    {  // setup
        Direction original(30.0);
        // exercise
        Direction copy(original);
        // verify
        assert(closeEnough(copy.getRadians(), original.getRadians()));
        assert(closeEnough(copy.getDegrees(), original.getDegrees()));
    }  // teardown

    void testSetRadians() const
    {  // setup
        Direction d;
        // exercise and verify
        d.setRadians(3.0);
        assert(closeEnough(d.getRadians(), 3.0));

        d.setRadians(2.0 * M_PI + 1.0);
        assert(closeEnough(d.getRadians(), 1.0));

        d.setRadians(-3.0);
        assert(closeEnough(d.getRadians(), -3.0));

        d.setRadians(-2.0 * M_PI - 1.0);
        assert(closeEnough(d.getRadians(), -1.0));
    }  // teardown

    void testSetDegrees() const
    {  // setup
        Direction d;
        // exercise and verify
        d.setDegrees(90.0);
        assert(closeEnough(d.getRadians(), M_PI / 2.0));

        d.setDegrees(180.0);
        assert(closeEnough(d.getRadians(), M_PI));

        d.setDegrees(360.0);
        assert(closeEnough(d.getRadians(), 0.0));

        d.setDegrees(-90.0);
        assert(closeEnough(d.getRadians(), -M_PI / 2.0));
    }  // teardown
};

