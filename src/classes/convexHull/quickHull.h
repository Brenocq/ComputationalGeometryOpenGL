#ifndef QUICKHULL_H
#define QUICKHULL_H
#include <vector>
#include "convexHull.h"

class QuickHull : public ConvexHull{
public:
  QuickHull();
  ~QuickHull();

  vector<Point*> run();
  void draw();

  bool pointInsideTriangle(Point* t1, Point* t2, Point* t3, Point* p);
};

#endif// QUICKHULL_H
