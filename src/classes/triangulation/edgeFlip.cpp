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

  /*//----- Get first point -----//
  firstPoint = getFirstPoint();

  //----- Sort by angle -----//
  sortedPoints = getSortedPoints();

  //----- Find convex hull -----//
  convexHull = findConvexHull();*/

  return _triangulation;
}

void EdgeFlip::draw(){

}
