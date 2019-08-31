#ifndef GRAHAM_H
#define GRAHAM_H
#include <vector>
#include "convexHull.h"

class Graham : public ConvexHull{
public:
  Graham();
  ~Graham();

  vector<Point*> run();

  Point* getFirstPoint();
  vector<Point*> getSortedPoints(Point* firstPoint);
  vector<Point*> findConvexHull(vector<Point*> sortedPoints);

  void colorPoints(Point* firstPoint, vector<Point*> sortedPoints, vector<Point*> convexHull);
};

#endif// GRAHAM_H
