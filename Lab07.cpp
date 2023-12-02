/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "physics.h"
#include "projectile.h"
#include <list>
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight)
   {
      ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      // Original GPS Satellite (already present)
      ptGPS.setMetersX(0.0);
      ptGPS.setMetersY(42164000.0);
      vGPS.setDxDy(-3100.0, 0.0);

      // New GPS Satellites
      ptGPS2.setMetersX(0.0);
      ptGPS2.setMetersY(-42165000.0);
      vGPS2.setDxDy(3100.0, 0.0);

      ptGPS3.setMetersX(42166000.0);
      ptGPS3.setMetersY(0.0);
      vGPS3.setDxDy(0.0, 3100.0);

      ptGPS4.setMetersX(-42166000.0);
      ptGPS4.setMetersY(0);
      vGPS4.setDxDy(0.0, -3100.0);

      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      angleShip = 0.0;
      angleEarth = 0.0;
      phaseStar = 0;

      // Initialize velocities for other objects using the same values as for GPS
      vHubble.setDxDy(3100.0, 0.0);
      vSputnik.setDxDy(3100.0, 0.0);
      vStarlink.setDxDy(3100.0, 0.0);
      vCrewDragon.setDxDy(3100.0, 0.0);
   }

   Position ptHubble;
   Position ptSputnik;
   Position ptStarlink;
   Position ptCrewDragon;
   Position ptShip;
   Position ptGPS, ptGPS2, ptGPS3, ptGPS4;
   Position ptStar;
   Position ptUpperRight;
   

   Velocity vGPS, vGPS2, vGPS3, vGPS4;
   Velocity vHubble;
   Velocity vSputnik;
   Velocity vStarlink;
   Velocity vCrewDragon;
   Velocity vShip;

   list<Projectile*> projectiles;

   unsigned char phaseStar;

   double angleShip;
   double angleEarth;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // perform all the game logic
   //

   double frameRate = 30.0;
   double hoursPerDay = 24.0;
   double minutesPerHour = 60.0;
   double secondsPerMinute = 60.0;
   double secondsPerDay = hoursPerDay * minutesPerHour * secondsPerMinute;
   double dilation = hoursPerDay;
   double t = dilation / frameRate * 50;
   double radiansInADay = 3.14159 * 2.0;
   double radiansPerFrame = (radiansInADay / frameRate) * (dilation / secondsPerDay);
   pDemo->angleEarth += radiansPerFrame;
   pDemo->phaseStar++;

   //
   // accept input
   //

   // move by a little
   Acceleration aThrustShip = Acceleration(0, Direction(pDemo->angleShip));
   if (pUI->isDown()) {
      aThrustShip = Acceleration(10, Direction(pDemo->angleShip));
   }
   if (pUI->isLeft()) {
      pDemo->angleShip -= 0.1;
   }
   if (pUI->isRight()) {
      pDemo->angleShip += 0.1;
   }
   if (pUI->isSpace()) {
      pDemo->projectiles.push_back(new Projectile(pDemo->ptShip, pDemo->angleShip));
   }

   // Update positions and velocities for each object
   Acceleration aGravityHubble = getGravity(pDemo->ptHubble);
   updatePosition(pDemo->ptHubble, pDemo->vHubble, aGravityHubble, t);
   updateVelocity(pDemo->vHubble, aGravityHubble, t);

   Acceleration aGravitySputnik = getGravity(pDemo->ptSputnik);
   updatePosition(pDemo->ptSputnik, pDemo->vSputnik, aGravitySputnik, t);
   updateVelocity(pDemo->vSputnik, aGravitySputnik, t);

   Acceleration aGravityStarlink = getGravity(pDemo->ptStarlink);
   updatePosition(pDemo->ptStarlink, pDemo->vStarlink, aGravityStarlink, t);
   updateVelocity(pDemo->vStarlink, aGravityStarlink, t);

   Acceleration aGravityCrewDragon = getGravity(pDemo->ptCrewDragon);
   updatePosition(pDemo->ptCrewDragon, pDemo->vCrewDragon, aGravityCrewDragon, t);
   updateVelocity(pDemo->vCrewDragon, aGravityCrewDragon, t); 

   // Update for additional GPS satellites
   Acceleration aGravity = getGravity(pDemo->ptGPS);
   updatePosition(pDemo->ptGPS, pDemo->vGPS, aGravity, t);
   updateVelocity(pDemo->vGPS, aGravity, t);

   Acceleration aGravityGPS2 = getGravity(pDemo->ptGPS2);
   updatePosition(pDemo->ptGPS2, pDemo->vGPS2, aGravityGPS2, t);
   updateVelocity(pDemo->vGPS2, aGravityGPS2, t);

   Acceleration aGravityGPS3 = getGravity(pDemo->ptGPS3);
   updatePosition(pDemo->ptGPS3, pDemo->vGPS3, aGravityGPS3, t);
   updateVelocity(pDemo->vGPS3, aGravityGPS3, t);

   Acceleration aGravityGPS4 = getGravity(pDemo->ptGPS4);
   updatePosition(pDemo->ptGPS4, pDemo->vGPS4, aGravityGPS4, t);
   updateVelocity(pDemo->vGPS4, aGravityGPS4, t);

   Acceleration aGravityShip = getGravity(pDemo->ptShip);
   aGravityShip.addAcc(aThrustShip);
   updatePosition(pDemo->ptShip, pDemo->vGPS, aGravityShip, t);
   updateVelocity(pDemo->vGPS, aGravityShip, t);

   // Check for collisions
   for (list<Projectile*>::iterator it = pDemo->projectiles.begin(); it != pDemo->projectiles.end(); it++)
   {
      if (computeDistance(pDemo->ptHubble, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptSputnik, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptStarlink, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptCrewDragon, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptGPS, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptGPS2, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptGPS3, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
      else if (computeDistance(pDemo->ptGPS4, (*it)->getPos()) < 200.0)
      {
         delete (*it);
         it = pDemo->projectiles.erase(it);
      }
   }


   //
   // draw everything
   //

   Position pt;
   ogstream gout(pt);

   // draw satellites
   gout.drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
   gout.drawHubble(pDemo->ptHubble, 0);
   gout.drawSputnik(pDemo->ptSputnik, 0);
   gout.drawStarlink(pDemo->ptStarlink, 0);
   gout.drawShip(pDemo->ptShip, pDemo->angleShip, pUI->isDown());
   gout.drawGPS(pDemo->ptGPS, 0);
   gout.drawGPS(pDemo->ptGPS2, 0);
   gout.drawGPS(pDemo->ptGPS3, 0);
   gout.drawGPS(pDemo->ptGPS4, 0);

   // draw parts
   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
   gout.drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
   pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
   gout.drawHubbleLeft(pt, pDemo->angleShip, Position(0, 0));      // notice only two parameters are set
   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
   gout.drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
   gout.drawStarlinkArray(pt, pDemo->angleShip, Position(0, 0));   // notice only two parameters are set

   // draw fragments
   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);

   // draw a single star
   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

   // draw the earth
   pt.setMeters(0.0, 0.0);
   gout.drawEarth(pt, pDemo->angleEarth);

   // draw the projectiles
   for (list<Projectile*>::iterator it = pDemo->projectiles.begin(); it != pDemo->projectiles.end(); it++)
   {
      (*it)->update();
      gout.drawProjectile((*it)->getPos());
   }
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);

   return 0;
}
