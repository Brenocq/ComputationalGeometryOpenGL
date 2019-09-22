#include "triangulation.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

using namespace std;

Triangulation::Triangulation(){
  _container = NULL;
}

Triangulation::~Triangulation(){}

void Triangulation::setPoints(Container *container){
  _container = container;
}
