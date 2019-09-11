#ifndef QUICKHULL_H
#define QUICKHULL_H
#include <vector>
#include "convexHull.h"

class QuickHull : public ConvexHull{
private:
    Point* firstPointsA;
    Point* firstPointsB;
public:
  QuickHull();
  ~QuickHull();

  vector<Point*> run();
  void findHull(vector<Point*> points, Point* P, Point* Q);
  void draw();

  void sortConvexHull();

  bool pointInsideTriangle(Point* t1, Point* t2, Point* t3, Point* p);
};

#endif// QUICKHULL_H
