#ifndef EARCLIPPING_H
#define EARCLIPPING_H
#include <vector>
#include "triangulation.h"

class EarClipping : public Triangulation{
public:
  EarClipping();
  ~EarClipping();

  Point* findFirstPoint();
  vector<Point*> sortPoints();

  void calculateInteriorAngles();
  void findGoodTriangle();

  vector<Triangle> run();
  void draw();
private:
  vector<Point*> _CCWpoints;
  vector<float> _interiorAngles;
};

#endif// EARCLIPPING_H
