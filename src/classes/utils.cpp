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
