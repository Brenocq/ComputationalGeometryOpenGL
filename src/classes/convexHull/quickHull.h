#ifndef GRAHAM_H
#define GRAHAM_H
#include <vector>
#include "convexHull.h"

class QuickHull : public ConvexHull{
public:
  QuickHull();
  ~QuickHull();

  vector<Point*> run();
  bool pointInsideTriangle(Point* t1, Point* t2, Point* t3, Point* p);
};

#endif// GRAHAM_H
