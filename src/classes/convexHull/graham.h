#ifndef GRAHAM_H
#define GRAHAM_H
#include <vector>
#include "convexHull.h"

class Graham : public ConvexHull{
public:
  Graham();
  ~Graham();

  vector<Point*> run();
  void draw();

  Point* getFirstPoint();
  vector<Point*> getSortedPoints();
  vector<Point*> findConvexHull();

  Point* pointInsideConvexHull();
private:
    Point* firstPoint;
    vector<Point*> sortedPoints;
    vector<Point*> convexHull;
};

#endif// GRAHAM_H
