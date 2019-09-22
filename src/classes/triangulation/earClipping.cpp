#include "earClipping.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

EarClipping::EarClipping():
Triangulation()
{}

EarClipping::~EarClipping()
{}

vector<Triangle> EarClipping::run(){
  if(_container->isEmpty()){
    return _triangulation;
  }
  //----- Sort by angle -----//
  _CCWpoints = sortPoints();

  //----- Calculate polygon interior angles -----//
  calculateInteriorAngles();

  //----- Triangulate -----//
  _triangulation.clear();
  if(_CCWpoints.size()>=3){
    while(_triangulation.size()<_container->getPoints().size()-2){
      findGoodTriangle();
      calculateInteriorAngles();
    }
  }

  return _triangulation;
}

Point* EarClipping::findFirstPoint(){
  if(_container->getPoints().size()<=0)
    return NULL;

  Point* firstPoint = _container->getPoints()[0];

  for(auto point : _container->getPoints()){
    if(point->y()<=firstPoint->y()){
      if(point->y()==firstPoint->y()){
        firstPoint = point->x()<firstPoint->x() ? point : firstPoint;
      }else{
        firstPoint = point;
      }
    }
  }
  return firstPoint;
}

vector<Point*> EarClipping::sortPoints(){
  Point* firstPoint = findFirstPoint();

  vector<pair<float,Point*>> sortedAngles;
  vector<Point*> sortedPoints;

  if(firstPoint==NULL)
    return sortedPoints;

  for(auto point : _container->getPoints()){
      float angle = atan2(firstPoint->y()-point->y(),(firstPoint->x()-point->x()));
      sortedAngles.push_back(make_pair(angle, point));
  }
  sort(sortedAngles.rbegin(), sortedAngles.rend());

  for(auto pointPair : sortedAngles){
    sortedPoints.push_back(pointPair.second);
  }
  return sortedPoints;
}

void EarClipping::calculateInteriorAngles(){
  _interiorAngles.clear();
  _interiorAngles.resize(_CCWpoints.size());
  for(int i = 0; i < int(_CCWpoints.size()); i++){
        int last = (i - 1 +  _CCWpoints.size()) % _CCWpoints.size();
        int next = (i + 1) % _CCWpoints.size();
        double x1 = _CCWpoints[i]->x() - _CCWpoints[last]->x();
        double y1 = _CCWpoints[i]->y() - _CCWpoints[last]->y();
        double x2 = _CCWpoints[next]->x() - _CCWpoints[i]->x();
        double y2 = _CCWpoints[next]->y() - _CCWpoints[i]->y();
        double theta1 = atan2(y1, x1)*180/M_PI;
        double theta2 = atan2(y2, x2)*180/M_PI;
        _interiorAngles[i] = 360-(180 + theta1 - theta2 + 360);
        while(_interiorAngles[i]>360)_interiorAngles[i]-=360;
        while(_interiorAngles[i]<0)_interiorAngles[i]+=360;
    }
    /*for(int i=0;i<_CCWpoints.size();i++){
      cout<<"vertex " <<i<<" -> "<<_interiorAngles[i]<<endl;
    }*/
}

void EarClipping::findGoodTriangle(){
  int bestPi = -1;
  int bestPiAngle = 360;
  for(int i=0; i<int(_CCWpoints.size()); i++){
    int last = (i - 1 + _CCWpoints.size()) % _CCWpoints.size();
    int next = (i + 1) % _CCWpoints.size();

    if(_interiorAngles[i]<180 && _interiorAngles[i]<bestPiAngle){
      Triangle triangle = {_CCWpoints[last],_CCWpoints[i],_CCWpoints[next]};
      bool goodTriangle = true;
      for(int j=0; j<int(_CCWpoints.size()); j++){
        if(j != i && j!=last && j!=next){
          if(utils::pointInTriangle(_CCWpoints[j], triangle.a, triangle.b, triangle.c)){
            goodTriangle=false;
          }
        }
      }

      if(goodTriangle){
        bestPi = i;
        bestPiAngle = _interiorAngles[i];
      }
    }
  }

  int bestLast = (bestPi - 1 + _CCWpoints.size()) % _CCWpoints.size();
  int bestNext = (bestPi + 1) % _CCWpoints.size();
  Triangle triangle = {_CCWpoints[bestLast],_CCWpoints[bestPi],_CCWpoints[bestNext]};

  _triangulation.push_back(triangle);
  _CCWpoints.erase(_CCWpoints.begin() + bestPi);
}



void EarClipping::draw(){
  _CCWpoints = sortPoints();// Points were removed while triangulating

  for(auto point : _container->getPoints()){
  point->setColor(0,0,0);
  }

  //----- Lines sorted points -----//
  /*if(_CCWpoints.size()>2){
    glLineWidth(1);
    glColor3f(1.0, 0.0, 0.0);
    for (unsigned int i = 1; i < _CCWpoints.size(); i++) {

      glBegin(GL_LINES);
      glVertex3f(_CCWpoints[i]->x(), _CCWpoints[i]->y(), 0.0);
      glVertex3f(_CCWpoints[i-1]->x(), _CCWpoints[i-1]->y(), 0.0);
      glEnd();
    }
  }*/

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
