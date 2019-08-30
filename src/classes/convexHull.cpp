#include "convexHull.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "utils.h"

using namespace std;

ConvexHull::ConvexHull(){
  _container = NULL;
}

ConvexHull::~ConvexHull(){}

void ConvexHull::setPoints(Container *container){
  _container = container;
}

void ConvexHull::run(){
  vector<pair<float,Point*>> sortedAngles;
  vector<Point*> convexHull;
  Point* firstPoint;

  if(_container->isEmpty()){
    return;
  }

  firstPoint = _container->getPoints()[0];
  //----- Get first point -----//
  for(auto point : _container->getPoints()){
    point->setColor(0,0,0);
  }

  for(auto point : _container->getPoints()){
    if(point!=firstPoint){
      if(point->y()<=firstPoint->y()){
        if(point->y()==firstPoint->y()){
          firstPoint = point->x()<firstPoint->x() ? point : firstPoint;
        }else{
          firstPoint = point;
        }
      }
    }
  }
  //----- Sort by angle -----//
  sortedAngles.push_back(make_pair(0, firstPoint));
  for(auto point : _container->getPoints()){
    if(point!=firstPoint){
      float angle = atan2(firstPoint->y()-point->y(),(firstPoint->x()-point->x()));
      sortedAngles.push_back(make_pair(angle, point));
    }
  }
  sort(sortedAngles.begin()+1, sortedAngles.end());

  // Uncomment to see the sorted points
  /*if(sortedAngles.size()>2){
    glLineWidth(1);
    glColor3f(1.0, 0.0, 0.0);
    for (unsigned int i = 1; i < sortedAngles.size(); i++) {
      glBegin(GL_LINES);
      glVertex3f(sortedAngles[i].second->x(), sortedAngles[i].second->y(), 0.0);
      glVertex3f(sortedAngles[i-1].second->x(), sortedAngles[i-1].second->y(), 0.0);
      glEnd();
    }
  }*/

  //----- Sort by angle -----//
  if(sortedAngles.size()>=3){
    convexHull.push_back(sortedAngles[0].second);
    convexHull.push_back(sortedAngles[1].second);
    for(unsigned int i=2; i<sortedAngles.size(); i++){
      float cp = utils::crossProduct(convexHull[convexHull.size()-2], convexHull[convexHull.size()-1], sortedAngles[i].second);
      if(cp==0){
        convexHull.pop_back();
        convexHull.push_back(sortedAngles[i].second);
      }else if(cp>0){
        convexHull.push_back(sortedAngles[i].second);
      }else{
        while(cp<=0 && convexHull.size()>2){
          convexHull.pop_back();
          cp = utils::crossProduct(convexHull[convexHull.size()-2], convexHull[convexHull.size()-1], sortedAngles[i].second);
        }
        convexHull.push_back(sortedAngles[i].second);
      }
    }
  }

  if(convexHull.size()>1){
    sortedAngles[0].second->setColor(1,0,0);

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
}
