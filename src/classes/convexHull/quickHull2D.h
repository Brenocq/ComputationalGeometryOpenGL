#ifndef QUICKHULL2D_H
#define QUICKHULL2D_H
#include <vector>
#include "convexHull.h"

class QuickHull2D : public ConvexHull{
private:
    Point* firstPointsA;
    Point* firstPointsB;
public:
  QuickHull2D();
  ~QuickHull2D();

  vector<Point*> run();
  void findHull(vector<Point*> points, Point* P, Point* Q);
  void draw();

  void sortConvexHull();

  bool pointInsideTriangle(Point* t1, Point* t2, Point* t3, Point* p);
};

#endif// QUICKHULL2D_H
