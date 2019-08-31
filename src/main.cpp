#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

#include "classes/container.h"
#include "classes/convexHull/convexHull.h"
#include "classes/convexHull/graham.h"
using namespace std;

//----- Window Parameters -----//
#define windowHeight 600
#define windowWidth 600
#define screenHeight 1080
#define screenWidth 1920

//----- Objects -----//
Container container;
ConvexHull *convexHullAlg = new Graham();

//----- Glut functions -----//
void draw();
void timer(int);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv){
  convexHullAlg->setPoints(&container);
  //----- Create window -----//
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition((screenWidth/2)-(windowWidth/2), (screenWidth/2)-(windowHeight/2));
  glutCreateWindow("Computational Geometry Problems");
  glClearColor(1.0, 1.0, 1.0, 1.0);// Clear window
  glutMouseFunc(mouse);
  glutDisplayFunc(draw);// Set the draw function
  glutTimerFunc(0, timer, 0);// Define timer function (loop function)
  glutMainLoop();

  return 0;
}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  container.draw2D();
  convexHullAlg->run();

  glutSwapBuffers();
}

void timer(int){
  glutPostRedisplay();

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
