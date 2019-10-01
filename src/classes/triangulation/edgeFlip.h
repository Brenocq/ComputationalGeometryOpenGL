#ifndef EDGEFLIP_H
#define EDGEFLIP_H
#include <vector>
#include "triangulation.h"

class EdgeFlip : public Triangulation{
public:
  EdgeFlip();
  ~EdgeFlip();

  void resetTriangulation();
  void insertPoint(Point *p);
  void flipEdges();
  void eraseOutPoints();
  void createNewTriangles(int indexTri, Point *p);
  bool turnToGoodTriangles(int indexTri1, int indexTri2);
  bool triangleSideBySide(Triangle tri1, Triangle tri2);
  bool triangleHasPoint(Triangle tri, Point *p);

  vector<Triangle> run();
  void draw();
private:
  vector<Point*> _outPoints;

};

#endif// EDGEFLIP_H
