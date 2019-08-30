#include "utils.h"
#include <stdlib.h>
#include <vector>

float utils::crossProduct(Point *p1, Point *p2, Point *p3){
  return (p2->x() - p1->x())*(p3->y() - p1->y()) - (p3->x() - p1->x())*(p2->y() - p1->y());
}
