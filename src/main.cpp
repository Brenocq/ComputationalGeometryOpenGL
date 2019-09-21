#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

#include "classes/container.h"
#include "classes/convexHull/convexHull.h"
#include "classes/convexHull/graham.h"
#include "classes/convexHull/quickHull2D.h"
#include "classes/convexHull/quickHull4D.h"
using namespace std;

//----- Window Parameters -----//
#define windowHeight 600
#define windowWidth 600
#define screenHeight 1080
#define screenWidth 1920

//----- Algorithms -----//
#define GRAHAM_2D 0
#define QUICKHULL_2D 1
#define QUICKHULL_4D 2

//----- Objects -----//
Container container;
ConvexHull *convexHullAlg = new Graham();

//----- Glut functions -----//
void draw();
void timer(int);
void mouse(int button, int state, int x, int y);
void menuInit();
void mainMenuHandler(int choice){}
void convexHullMenuHandler(int choice);

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

    glutCreateMenu(mainMenuHandler);
    glutAddSubMenu("ConvexHull", convexHullSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    cout<<"Welcome! You can left-click to add points or right-click to select another algorithm.\n";
    cout<<"Graham 2D selected\n";
}

void convexHullMenuHandler(int choice) {
    // Define what will do on each menu option
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

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  convexHullAlg->draw();
  container.draw2D();

  glutSwapBuffers();
}

void timer(int){
  glutPostRedisplay();
  convexHullAlg->run();
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
