#ifndef CONVEXHULL_H
#define CONVEXHULL_H
#include <vector>
#include "../container.h"

class ConvexHull{
public:
  ConvexHull();
  ~ConvexHull();

  void setPoints(Container *container);
  virtual vector<Point*> run() = 0;
  virtual void draw() = 0;

protected:
  Container *_container;
};

#endif// CONVEXHULL_H
