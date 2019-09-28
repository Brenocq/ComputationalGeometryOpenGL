#ifndef EDGEFLIP_H
#define EDGEFLIP_H
#include <vector>
#include "triangulation.h"

class EdgeFlip : public Triangulation{
public:
  EdgeFlip();
  ~EdgeFlip();

  void resetTriangulation();
  void insertPoint(Point* p);
  void createNewTriangles(int indexTri, Point* p);

  vector<Triangle> run();
  void draw();
private:
  vector<Point*> _outPoints;

};

#endif// EDGEFLIP_H
