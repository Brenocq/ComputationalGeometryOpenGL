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

bool utils::pointInTriangle(Point *p, Point *v1, Point *v2, Point *v3){
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = crossProduct(p, v1, v2);
    d2 = crossProduct(p, v2, v3);
    d3 = crossProduct(p, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

vector<float> utils::anglesTriangle(Point *p1, Point *p2, Point *p3){
  // Only for 2D points

  vector<float> res;

  // Size each side
  float a = sqrt( pow(p2->x()-p1->x(),2) + pow(p2->y()-p1->y(),2));
  float b = sqrt( pow(p3->x()-p2->x(),2) + pow(p3->y()-p2->y(),2));
  float c = sqrt( pow(p1->x()-p3->x(),2) + pow(p1->y()-p3->y(),2));

  // Angles (cosines law)
  float A = acos(( b*b + c*c - a*a )/( 2*b*c ));
  float B = acos(( c*c + a*a - b*b )/( 2*a*c ));
  float C = acos(( a*a + b*b - c*c )/( 2*a*b ));

  res.push_back(A);
  res.push_back(B);
  res.push_back(C);

  return res;
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
