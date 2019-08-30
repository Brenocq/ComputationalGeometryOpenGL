#include "container.h"

Container::Container(){

}
Container::~Container(){}

void Container::addPoint(float x, float y, float z){
  Point *p = new Point(x,y,z);
  points.push_back(p);
}

void Container::cleanPoints(){
  points.clear();
}

vector<Point*> Container::getPoints(){
  return points;
}

bool Container::isEmpty(){
  return points.size()==0;
}

void Container::draw2D(){
  for(auto point : points)
      point->draw2D();
}
