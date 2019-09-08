#include "graham.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

Graham::Graham():
ConvexHull()
{}

Graham::~Graham()
{}

vector<Point*> Graham::run(){
  if(_container->isEmpty()){
    return convexHull;
  }

  //----- Get first point -----//
  firstPoint = getFirstPoint();

  //----- Sort by angle -----//
  sortedPoints = getSortedPoints(firstPoint);

  //----- Find convex hull -----//
  convexHull = findConvexHull(sortedPoints);

  return convexHull;
}

Point* Graham::getFirstPoint(){
  Point* firstPoint = _container->getPoints()[0];

  // What happens if you replace “rightmost lowest point”by ¨a point in the interior of the convex hull?
  // Comment the for loop
  for(auto point : _container->getPoints()){
    // What happens if you replace “lowest”by ”highest”?
    // if(point->y()>=firstPoint->y()){
    if(point->y()<=firstPoint->y()){
      if(point->y()==firstPoint->y()){
        firstPoint = point->x()<firstPoint->x() ? point : firstPoint;
        // What happens if you replace “strictly left” by left”?
        // firstPoint = point->x()<=firstPoint->x() ? point : firstPoint;
      }else{
        firstPoint = point;
      }
    }
  }
  return firstPoint;
}

vector<Point*> Graham::getSortedPoints(Point* firstPoint){
    vector<pair<float,Point*>> sortedAngles;
    vector<Point*> sortedPoints;

    for(auto point : _container->getPoints()){
        float angle = atan2(firstPoint->y()-point->y(),(firstPoint->x()-point->x()));
        if(firstPoint->y()==point->y() && firstPoint->x()<point->x()){
          angle*=-1;
        }
        sortedAngles.push_back(make_pair(angle, point));
    }
    sort(sortedAngles.begin(), sortedAngles.end());

    sortedPoints.push_back(firstPoint);
    for(auto pointPair : sortedAngles){
      sortedPoints.push_back(pointPair.second);
    }
    return sortedPoints;
}

vector<Point*> Graham::findConvexHull(vector<Point*> sortedPoints){
  vector<Point*> convexHull;
  if(sortedPoints.size()>=3){
    convexHull.push_back(sortedPoints[0]);// firstPoint
    convexHull.push_back(sortedPoints[1]);
    for(unsigned int i=2; i<sortedPoints.size(); i++){
      float cp = utils::crossProduct(convexHull[convexHull.size()-2], convexHull[convexHull.size()-1], sortedPoints[i]);
      if(cp==0){
        convexHull.pop_back();
        convexHull.push_back(sortedPoints[i]);
      }else if(cp>0){
        convexHull.push_back(sortedPoints[i]);
      }else{
        while(cp<=0 && convexHull.size()>2){
          convexHull.pop_back();
          cp = utils::crossProduct(convexHull[convexHull.size()-2], convexHull[convexHull.size()-1], sortedPoints[i]);
        }
        convexHull.push_back(sortedPoints[i]);
      }
    }
  }
  return convexHull;
}

void Graham::draw(){
    if(firstPoint==NULL || sortedPoints.size()==0 || convexHull.size()==0)
        return;
    // Set all points as black
    for(auto point : _container->getPoints()){
    point->setColor(0,0,0);
    }

    //----- Sorted points lines -----//
    if(sortedPoints.size()>2){
    glLineWidth(1);
    glColor3f(1.0, 0.0, 0.0);
    for (unsigned int i = 1; i < sortedPoints.size(); i++) {
      glBegin(GL_LINES);
      glVertex3f(sortedPoints[i]->x(), sortedPoints[i]->y(), 0.0);
      glVertex3f(sortedPoints[i-1]->x(), sortedPoints[i-1]->y(), 0.0);
      glEnd();
    }
    }

    //----- Convex hull lines and points -----//
    if(convexHull.size()>1){
    glLineWidth(2);
    glColor3f(0.0, 0.0, 1.0);
    for (unsigned int i = 1; i < convexHull.size(); i++) {
      convexHull[i]->setColor(0,0,1);
      glBegin(GL_LINES);
      glVertex3f(convexHull[i]->x(), convexHull[i]->y(), 0.0);
      glVertex3f(convexHull[i-1]->x(), convexHull[i-1]->y(), 0.0);
      glEnd();
    }
    glBegin(GL_LINES);
    glVertex3f(convexHull.back()->x(), convexHull.back()->y(), 0.0);
    glVertex3f(convexHull.front()->x(), convexHull.front()->y(), 0.0);
    glEnd();
    }

    //----- First point -----//
    firstPoint->setColor(1,0,0);
}
