#ifndef QUICKHULL4D_H
#define QUICKHULL4D_H
#include <vector>
#include "convexHull.h"

class QuickHull4D : public ConvexHull{
private:
    vector<Point*> firstPoints;
public:
  QuickHull4D();
  ~QuickHull4D();

  vector<Point*> run();
  void findHull(vector<Point*> points, Point* P, Point* Q, Point* R, Point* S);
  void draw();

  void sortConvexHull();

  bool pointInside(Point* t1, Point* t2, Point* t3, Point* t4, Point* t5, Point* p);
  float hyperVolume(Point* t1, Point* t2, Point* t3, Point* t4, Point* t5);
  float volume(Point* t1, Point* t2, Point* t3, Point* t4);
  float determinant(float matrix[5][5], int n);
};

#endif// QUICKHULL4D_H
