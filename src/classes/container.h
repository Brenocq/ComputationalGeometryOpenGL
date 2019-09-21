#ifndef CONTAINER_H
#define CONTAINER_H
#include <vector>
#include "point.h"

class Container{
public:
  Container();
  ~Container();

  void addPoint(float x, float y, float z=0, float w=0);
  void cleanPoints();
  vector<Point*> getPoints();
  bool isEmpty();

  void draw2D();
private:
  vector<Point*> points;
};


#endif
