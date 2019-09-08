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
  vector<Point*> getSortedPoints(Point* firstPoint);
  vector<Point*> findConvexHull(vector<Point*> sortedPoints);
private:
    Point* firstPoint;
    vector<Point*> sortedPoints;
    vector<Point*> convexHull;
};

#endif// GRAHAM_H
