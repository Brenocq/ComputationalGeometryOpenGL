#ifndef UTILS_H
#define UTILS_H
#include "point.h"

namespace utils{
  float crossProduct(Point *p1, Point *p2, Point *p3);
  float distancePointLine(Point *pl1, Point *pl2, Point *p);
  float distancePointHyperplane(std::vector<Point*> point, unsigned int dim);
  float angleTwoPoints(Point *p1, Point *p2);
  bool pointInTriangle(Point *p, Point *v1, Point *v2, Point *v3);
  vector<float> anglesTriangle(Point *p1, Point *p2, Point *p3);
  float normVector(Point* Nvector);
  bool  checkSum(float sum, std::vector<float> vals);
  unsigned long int factorial(unsigned int n);
  float distancePointHyperplane();
  float determinant(float matrix[5][5], int n);
  float normVector(Point* Nvector);
  bool  checkSum(float sum, float vec[]);
  unsigned long int factorial(unsigned int n);
}

#endif// UTILS_H
