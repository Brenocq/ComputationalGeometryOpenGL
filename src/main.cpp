#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <iomanip>

#include "classes/container.h"
#include "classes/convexHull/convexHull.h"
#include "classes/convexHull/graham.h"
#include "classes/convexHull/quickHull2D.h"
#include "classes/convexHull/quickHull4D.h"
#include "classes/triangulation/triangulation.h"
#include "classes/triangulation/earClipping.h"
#include "classes/triangulation/edgeFlip.h"
using namespace std;

//----- Window Parameters -----//
#define windowHeight 600
#define windowWidth 600
#define screenHeight 1080
#define screenWidth 1920

//----- Algorithms -----//
int currAlg;
// [0-9] -> ConvexHull
#define GRAHAM_2D 0
#define QUICKHULL_2D 1
#define QUICKHULL_4D 2
// [10-19] -> Triangulation
#define EARCLIPPING_2D 10
#define EDGEFLIP_2D 11

//----- Objects -----//
Container container;
ConvexHull *convexHullAlg = new Graham();
Triangulation *triangulationAlg = new EarClipping();

//----- Glut functions -----//
void draw();
void timer(int);
void mouse(int button, int state, int x, int y);
void menuInit();
void mainMenuHandler(int choice){}
void convexHullMenuHandler(int choice);
void triangulationMenuHandler(int choice);

int main(int argc, char** argv){
  convexHullAlg->setPoints(&container);
  //----- Create window -----//
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition((screenWidth/2)-(windowWidth/2), (screenWidth/2)-(windowHeight/2));
  glutCreateWindow("Computational Geometry Problems");
  glClearColor(1.0, 1.0, 1.0, 1.0);// Clear window
  //----- Handles -----//
  menuInit();// Create menu options
  glutMouseFunc(mouse);// Allow to add points
  glutDisplayFunc(draw);// Set the draw function
  glutTimerFunc(0, timer, 0);// Define timer function (loop function)
  glutMainLoop();

  return 0;
}

void menuInit(){
    // Create the menu options
    int convexHullSubMenu = glutCreateMenu(convexHullMenuHandler);
    glutAddMenuEntry("Graham 2D", GRAHAM_2D);
    glutAddMenuEntry("QuickHull 2D", QUICKHULL_2D);
    glutAddMenuEntry("QuickHull 4D", QUICKHULL_4D);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    int triangulationSubMenu = glutCreateMenu(triangulationMenuHandler);
    glutAddMenuEntry("EarClipping 2D", EARCLIPPING_2D);
    glutAddMenuEntry("EdgeFlip 2D", EDGEFLIP_2D);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutCreateMenu(mainMenuHandler);
    glutAddSubMenu("ConvexHull", convexHullSubMenu);
    glutAddSubMenu("Triangulation", triangulationSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    cout<<"Welcome! You can left-click to add points or right-click to select another algorithm.\n";
    cout<<"Graham 2D selected\n";

    // QuickHull 4D (aux points)
    /*container.addPoint(   0,   0,   0,   0);
    container.addPoint(-0.1, 0.1,   0,   0);
    container.addPoint(-0.4, 0.1, 0.2,   0);
    container.addPoint(  -2,   0,  -1,   0);
    container.addPoint(  -1,  -2,  -1,   0);
    container.addPoint(   1,   3,  -1,   0);
    container.addPoint(   3,  -1,  -2,   0);
    container.addPoint(   0,   0,   3,   0);
    container.addPoint(   0,   0,   0,  10);
    container.addPoint(   0,   0,   0, -10);*/

   container.addPoint(0.6443,    0.0855,    0.0305,    0.1734);
   container.addPoint(0.3786,    0.2625,    0.7441,    0.3909);
   container.addPoint(0.8116,    0.8010,    0.5000,    0.8314);
   container.addPoint(0.5328,    0.0292,    0.4799,    0.8034);
   container.addPoint(0.3507,    0.9289,    0.9047,    0.0605);
   container.addPoint(0.9390,    0.7303,    0.6099,    0.3993);
   container.addPoint(0.8759,    0.4886,    0.6177,    0.5269);
   container.addPoint(0.5502,    0.5785,    0.8594,    0.4168);
   container.addPoint(0.6225,    0.2373,    0.8055,    0.6569);
   container.addPoint(0.5870,    0.4588,    0.5767,    0.6280);
   container.addPoint(0.2077,    0.9631,    0.1829,    0.2920);
   container.addPoint(0.3012,    0.5468,    0.2399,    0.4317);
   container.addPoint(0.4709,    0.5211,    0.8865,    0.0155);
   container.addPoint(0.2305,    0.2316,    0.0287,    0.9841);
   container.addPoint(0.8443,    0.4889,    0.4899,    0.1672);
   container.addPoint(0.1948,    0.6241,    0.1679,    0.1062);
   container.addPoint(0.2259,    0.6791,    0.9787,    0.3724);
   container.addPoint(0.1707,    0.3955,    0.7127,    0.1981);
   container.addPoint(0.2277,    0.3674,    0.5005,    0.4897);
   container.addPoint(0.4357,    0.9880,    0.4711,    0.3395);
   container.addPoint(0.3111,    0.0377,    0.0596,    0.9516);
   container.addPoint(0.9234,    0.8852,    0.6820,    0.9203);
   container.addPoint(0.4302,    0.9133,    0.0424,    0.0527);
   container.addPoint(0.1848,    0.7962,    0.0714,    0.7379);
   container.addPoint(0.9049,    0.0987,    0.5216,    0.2691);
   container.addPoint(0.9797,    0.2619,    0.0967,    0.4228);
   container.addPoint(0.4389,    0.3354,    0.8181,    0.5479);
   container.addPoint(0.1111,    0.6797,    0.8175,    0.9427);
   container.addPoint(0.2581,    0.1366,    0.7224,    0.4177);
   container.addPoint(0.4087,    0.7212,    0.1499,    0.9831);
   container.addPoint(0.5949,    0.1068,    0.6596,    0.3015);
   container.addPoint(0.2622,    0.6538,    0.5186,    0.7011);
   container.addPoint(0.6028,    0.4942,    0.9730,    0.6663);
   container.addPoint(0.7112,    0.7791,    0.6490,    0.5391);
   container.addPoint(0.2217,    0.7150,    0.8003,    0.6981);
   container.addPoint(0.1174,    0.9037,    0.4538,    0.6665);
   container.addPoint(0.2967,    0.8909,    0.4324,    0.1781);
   container.addPoint(0.3188,    0.3342,    0.8253,    0.1280);
   container.addPoint(0.4242,    0.6987,    0.0835,    0.9991);
   container.addPoint(0.5079,    0.1978,    0.1332,    0.1711);

   /*RES
     1
     4
     5
     6
     9
    11
    13
    14
    15
    16
    17
    18
    20
    21
    22
    23
    24
    25
    26
    28
    29
    30
    31
    33
    36
    38
    39
    40
    */

    // Define ID of each point (to compare with matlab output)
    for (int i = 0; i < container.getPoints().size(); i++) {
      container.getPoints()[i]->setID(i+1);
    }
}

void convexHullMenuHandler(int choice) {
  // Define what will do on each menu option
  currAlg = choice;
	switch(choice) {
		case GRAHAM_2D:
			cout<<"Graham 2D selected\n";
      //container.cleanPoints();
      convexHullAlg = new Graham();
      convexHullAlg->setPoints(&container);
			break;
		case QUICKHULL_2D:
			cout<<"QuickHull 2D selected\n";
      //container.cleanPoints();
      convexHullAlg = new QuickHull2D();
      convexHullAlg->setPoints(&container);
			break;
    case QUICKHULL_4D:
      cout<<"QuickHull 4D selected\n";
      //container.cleanPoints();
      convexHullAlg = new QuickHull4D();
      convexHullAlg->setPoints(&container);
    break;
	}
}

void triangulationMenuHandler(int choice) {
  // Define what will do on each menu option
  currAlg = choice;
	switch(choice) {
    case EARCLIPPING_2D:
      cout<<"EarClipping 2D selected\n";
      //container.cleanPoints();
      triangulationAlg = new EarClipping();
      triangulationAlg->setPoints(&container);
      break;
		case EDGEFLIP_2D:
			cout<<"EdgeFlip 2D selected\n";
      //container.cleanPoints();
      triangulationAlg = new EdgeFlip();
      triangulationAlg->setPoints(&container);
			break;
	}
}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  if(currAlg<10){
    convexHullAlg->draw();
    container.draw2D();
  }else if(currAlg<20){
    triangulationAlg->draw();
    container.draw2D();
  }

  glutSwapBuffers();
}

void timer(int){
  static int lastQtdPoints=0;
  static int lastAlg=0;

  glutPostRedisplay();

  if(lastQtdPoints!=container.getPoints().size() || currAlg!=lastAlg){
    lastAlg = currAlg;
    lastQtdPoints = container.getPoints().size();

    if(currAlg<10){
      // Calculate convex hull
      vector<Point*> result = convexHullAlg->run();

      // Print points convex hull
      cout << setprecision(2);
      cout<<"Result ConvexHull ("<<result.size()<<")"<<endl;

      for(auto p : result){
        cout<<p->getID()<<" -> ";
        for (int i = 0; i < 4; i++)
            cout<<(i==0?"(":"")<<p->getCord()[i]<<(i!=3?",":")\n");
      }

    }else if(currAlg<20){

      triangulationAlg->run();
    }
  }
  glutTimerFunc(1000/60, timer, 0);// Call timer function as fast as possible
}

void mouse(int button, int state, int x, int y)
{
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    float mouseX, mouseY;
    mouseX = 2*((float(x)/windowWidth)-0.5);
    mouseY = -2*((float(y)/windowHeight)-0.5);
    container.addPoint(mouseX,mouseY);
  }
}
