#ifndef EDGEFLIP_H
#define EDGEFLIP_H
#include <vector>
#include "triangulation.h"

class EdgeFlip : public Triangulation{
public:
  EdgeFlip();
  ~EdgeFlip();

  vector<Triangle> run();
  void draw();
private:

};

#endif// EDGEFLIP_H
