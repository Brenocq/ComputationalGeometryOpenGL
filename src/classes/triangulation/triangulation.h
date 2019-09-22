#ifndef TRIANGULATION_H
#define TRIANGULATION_H
#include <vector>
#include "../container.h"

typedef struct _triangle{
  Point* a;
  Point* b;
  Point* c;
}Triangle;

class Triangulation{
public:
  Triangulation();
  ~Triangulation();

  void setPoints(Container *container);
  virtual vector<Triangle> run() = 0;
  virtual void draw() = 0;

protected:
  Container *_container;
  vector<Triangle> _triangulation;
};

#endif// TRIANGULATION_H
