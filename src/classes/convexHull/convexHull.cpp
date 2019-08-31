#include "convexHull.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

using namespace std;

ConvexHull::ConvexHull(){
  _container = NULL;
}

ConvexHull::~ConvexHull(){}

void ConvexHull::setPoints(Container *container){
  _container = container;
}
