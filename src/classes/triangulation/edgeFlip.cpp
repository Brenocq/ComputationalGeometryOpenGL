#include "edgeFlip.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"
#include "../convexHull/graham.h"

EdgeFlip::EdgeFlip():
Triangulation()
{}

EdgeFlip::~EdgeFlip()
{}

vector<Triangle> EdgeFlip::run(){
  if(_container->isEmpty()){
    return _triangulation;
  }

  resetTriangulation();
  //----- Create new triangle with point -----//
  for(auto point : _container->getPoints()){
    insertPoint(point);
  }

  //----- Try: brute force -----//
  bool changed = true;
  while(changed){
    changed = false;
    for (int i = 0; i < int(_triangulation.size()); i++) {
      for (int j = i+1; j < int(_triangulation.size()); j++) {
        changed = turnToGoodTriangles(i, j);
      }
    }
  }

  return _triangulation;
}

void EdgeFlip::resetTriangulation(){
  _triangulation.clear();
  _outPoints.push_back(new Point(-1,-1));
  _outPoints.push_back(new Point(1,-1));
  _outPoints.push_back(new Point(0,1));
  Triangle outTriangle = {_outPoints[0], _outPoints[1], _outPoints[2]};
  _triangulation.push_back(outTriangle);
}

void EdgeFlip::insertPoint(Point* p){
  for(int i=0;i<int(_triangulation.size());i++){
    Triangle triangle = _triangulation[i];
    if(utils::pointInTriangle(p, triangle.a, triangle.b, triangle.c)){
      createNewTriangles(i, p);
      return;
    }
  }
}

void EdgeFlip::createNewTriangles(int indexTri, Point* p){
  Triangle t = _triangulation[indexTri];
  Triangle triA = {t.a, t.b, p};
  Triangle triB = {t.b, t.c, p};
  Triangle triC = {t.c, t.a, p};
  _triangulation.push_back(triA);
  _triangulation.push_back(triB);
  _triangulation.push_back(triC);

  _triangulation.erase(_triangulation.begin() + indexTri);
}


bool EdgeFlip::triangleSideBySide(Triangle tri1, Triangle tri2){
  vector<Point*> commonPoint;

  vector<Point*> pointsTri1 = {tri1.a, tri1.b, tri1.c};
  vector<Point*> pointsTri2 = {tri2.a, tri2.b, tri2.c};

  // Get common points in tri1 and tri2
  for(auto point1 : pointsTri1){
    for(auto point2 : pointsTri2){
      if(point1 == point2){
        commonPoint.push_back(point1);
      }
    }
  }
  return commonPoint.size()==2;
}

bool EdgeFlip::turnToGoodTriangles(int indexTri1, int indexTri2){
  //Caution! indexTri2 must be grater than indexTri1
  Triangle tri1 = _triangulation[indexTri1];
  Triangle tri2 = _triangulation[indexTri2];

  // Calculate interior angles of tri1 and tri2
  vector<float> anglesTri1 = utils::anglesTriangle(tri1.a, tri1.b, tri1.c);
  vector<float> anglesTri2 = utils::anglesTriangle(tri2.a, tri2.b, tri2.c);

  vector<Point*> pointsTri1 = {tri1.a, tri1.b, tri1.c};
  vector<Point*> pointsTri2 = {tri2.a, tri2.b, tri2.c};
  vector<Point*> commonPoint;
  vector<Point*> uniquePoint;

  // Get common points in tri1 and tri2
  for(auto point1 : pointsTri1){
    for(auto point2 : pointsTri2){
      if(point1 == point2){
        commonPoint.push_back(point1);
      }
    }
  }
  if(commonPoint.size()!=2){
    // Must have two points in common to work
    return false;
  }

  // Get unique points of tri1 and tri2
  for(auto point1 : pointsTri1){
    bool unique = true;
    for(auto point2 : commonPoint){
      if(point1==point2){
        unique = false;
      }
    }
    if(unique){
      uniquePoint.push_back(point1);
    }
  }
  for(auto point1 : pointsTri2){
    bool unique = true;
    for(auto point2 : commonPoint){
      if(point1==point2){
        unique = false;
      }
    }
    if(unique){
      uniquePoint.push_back(point1);
    }
  }

  Triangle tri3 = {uniquePoint[0],uniquePoint[1],commonPoint[0]};
  Triangle tri4 = {uniquePoint[0],uniquePoint[1],commonPoint[1]};

  // Check if the polygon formed by the points is convex
  ConvexHull *convexHull = new Graham();
  Container container;
  container.addPoint(uniquePoint[0]->x(), uniquePoint[0]->y());
  container.addPoint(uniquePoint[1]->x(), uniquePoint[1]->y());
  container.addPoint(commonPoint[0]->x(), commonPoint[0]->y());
  container.addPoint(commonPoint[1]->x(), commonPoint[1]->y());
  convexHull->setPoints(&container);
  convexHull->run();
  vector<Point*> CH = convexHull->getConvexHull();
  if(CH.size()!=4){
    return false;
  }

  // Calculate interior angles of tri3 and tri4
  vector<float> anglesTri3 = utils::anglesTriangle(tri3.a, tri3.b, tri3.c);
  vector<float> anglesTri4 = utils::anglesTriangle(tri4.a, tri4.b, tri4.c);

  // Compare angles to decide if will flip or not (delete indexTri1, indexTri2 and add new)
  float minAngle12=2*M_PI, minAngle34=2*M_PI;
  for(auto angle : anglesTri1){
    minAngle12 = min(minAngle12, angle);
  }
  for(auto angle : anglesTri2){
    minAngle12 = min(minAngle12, angle);
  }

  for(auto angle : anglesTri3){
    minAngle34 = min(minAngle34, angle);
  }
  for(auto angle : anglesTri4){
    minAngle34 = min(minAngle34, angle);
  }

  if(minAngle12<minAngle34){
    _triangulation.erase(_triangulation.begin() + indexTri2);
    _triangulation.erase(_triangulation.begin() + indexTri1);
    _triangulation.push_back(tri3);
    _triangulation.push_back(tri4);
    return true;
  }
  return false;
}

void EdgeFlip::draw(){
  //----- Points -----//
  for(auto point : _container->getPoints()){
    point->setColor(0, 0, 0);
  }
  //----- Triangles -----//
  if(_triangulation.size()>0){
    for(auto triangle : _triangulation){
      glLineWidth(2);
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(triangle.a->x(), triangle.a->y(), 0.0);
      glVertex3f(triangle.b->x(),triangle.b->y(), 0.0);
      glVertex3f(triangle.b->x(),triangle.b->y(), 0.0);
      glVertex3f(triangle.c->x(),triangle.c->y(), 0.0);
      glVertex3f(triangle.c->x(),triangle.c->y(), 0.0);
      glVertex3f(triangle.a->x(),triangle.a->y(), 0.0);
      glEnd();
    }
  }
}
