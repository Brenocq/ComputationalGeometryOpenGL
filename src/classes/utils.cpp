#include "utils.h"
#include <stdlib.h>
#include <vector>
#include <math.h>

float utils::crossProduct(Point *p1, Point *p2, Point *p3){
  return (p2->x() - p1->x())*(p3->y() - p1->y()) - (p3->x() - p1->x())*(p2->y() - p1->y());
}

float utils::distancePointLine(Point *pl1, Point *pl2, Point *p){
    float a,b,c;
    a = pl1->y() - pl2->y();
    b = pl2->x() - pl1->x();
    c = pl1->x() * pl2->y() - pl2->x() * pl1->y();

    return abs(a * p->x() + b * p->y() + c) / sqrt(a * a + b * b);
}

float utils::angleTwoPoints(Point *p1, Point *p2){
  return atan2(p1->y() - p2->y(), p1->x() - p2->x());
}

float utils::pointInTriangle(Point *p, Point *v1, Point *v2, Point *v3){
  float d1, d2, d3;
  bool has_neg, has_pos;

  d1 = crossProduct(p, v1, v2);
  d2 = crossProduct(p, v2, v3);
  d3 = crossProduct(p, v3, v1);

  has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
  has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

  return !(has_neg && has_pos);
}

bool utils::checkSum(float sum, std::vector<float> vals) {
    //Maybe we should set and epsilon due to floating point inaccuracies
    float epsilon = 0;
    float buffer = 0;

    for ( std::size_t i = 0; i < vals.size(); i++ ){
	       buffer += vals[i];
	}

    if ( sum - epsilon <= buffer && sum + epsilon >= buffer ) {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned long int utils::factorial(unsigned int n) {
	unsigned long fact = 1;
	int i;

	for (i = 1; i <= n; i++)
		fact = fact * i;

	return fact;
}

float utils::distancePointHyperplane() {
    /*float //upper part

    return /normVector(planeVec.getCord());*/
    return -1;
}

float utils::normVector(Point* Nvector) {
    std::vector<float> coords = Nvector->getCord();
    float sum = 0;
    for (int i = 0 ; i < coords.size() ; i++) {
        sum += coords[i] * coords[i];
    }

    return sqrt(sum);
}