#include "edgeFlip.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

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
  for(int i=0;i<_triangulation.size();i++){
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

void EdgeFlip::turnToGoodTriangles(int indexTri1, int indexTri2){
  Triangle tri1 = _triangulation[indexTri1];
  Triangle tri2 = _triangulation[indexTri2];

  vector<float> anglesTri1 = utils::anglesTriangle(tri1.a, tri1.b, tri1.c);
  vector<float> anglesTri2 = utils::anglesTriangle(tri2.a, tri2.b, tri2.c);

  Triangle tri3, tri4;
  // Find triangle tri4 and tri3
  // Calculate angles tri4 and tri3
  // Compare angles to decide if will flip or not (delete indexTri1, indexTri2 and add new)

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
