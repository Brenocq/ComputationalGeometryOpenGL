#ifndef CONVEXHULL_H
#define CONVEXHULL_H
#include <vector>
#include "container.h"

class ConvexHull{
public:
  ConvexHull();
  ~ConvexHull();

  void setPoints(Container *container);
  void run();

private:
  Container *_container;
};

#endif// CONVEXHULL_H
