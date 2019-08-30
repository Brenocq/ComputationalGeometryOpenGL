#ifndef POINT_H
#define POINT_H
#include <vector>
using namespace std;

class Point{
public:
  Point();
  Point(float _x, float _y, float _z=0);
  ~Point();

  void draw2D();
  //----- Setters -----//
  void setPoint(float _x, float _y, float _z=0);
  void setX(float _x);
  void setY(float _y);
  void setZ(float _z);
  void setColor(float r, float g, float b);
  //----- Getters -----//
  float x();
  float y();
  float z();

private:
  vector<float> cord;
  float radius;
  vector<float> color;
};


#endif// POINT_H
