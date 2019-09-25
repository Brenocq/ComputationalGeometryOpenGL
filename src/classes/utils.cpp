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


float utils::determinant(float matrix[5][5], int n) {
   float det = 0;
   float submatrix[5][5];
   if (n == 2)
      return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
   else {
      for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
               int subj = 0;
               for (int j = 0; j < n; j++) {
                  if (j == x)
                  continue;
                  submatrix[subi][subj] = matrix[i][j];
                  subj++;
               }
               subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
      }
   }
   return det;
}