#include "quickHull4D.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

QuickHull4D::QuickHull4D():
ConvexHull()
{}

QuickHull4D::~QuickHull4D()
{}

vector<Point*> QuickHull4D::run(){
    vector<Point*> S1, S2, S3, S4;
    Point *p[4];// Maximum or minimum points (belong to the convexHull)
    convexHull.clear();

    if(_container->getPoints().size()<4)
        return convexHull;

    //----- Find min/max points ("left most", "right most")-----//
    p[0] = _container->getPoints()[0];
    p[1] = _container->getPoints()[0];
    p[2] = _container->getPoints()[0];
    p[3] = _container->getPoints()[0];
    for(auto point : _container->getPoints()){
        if(point->x()<p[0]->x())
            p[0] = point;
        if(point->x()>p[1]->x())
            p[1] = point;
        if(point->y()<p[2]->y())
            p[2] = point;
        if(point->y()>p[3]->y())
            p[3] = point;
    }
    for(auto pointA : p){
      int qtdEqual = 0;
      for(auto pointB : p){
        if(pointA==pointB)
          qtdEqual++;
      }
      if(qtdEqual>1)
        cout<<"[Warning] Same initial point on the QuickHull4D algorithm.\n";
    }

    for(auto point : p){
      convexHull.push_back(point);
      firstPoints.push_back(point);// To draw
    }

    //----- Divide points in two subsets -----//
    for(auto point : _container->getPoints()){
        float position = hyperVolume(firstPoints[0], firstPoints[1], firstPoints[2], firstPoints[3], point);
        // On the line or to one side
        if(position>0 && abs(position)>0.001){
            S1.push_back(point);
        }else if(position<0 && abs(position)>0.001){
            S2.push_back(point);
        }
    }

    //----- Divide points in for subsets -----//
    findHull(S1, p[0], p[1], p[2], p[3]);
    findHull(S2, p[3], p[2], p[1], p[0]);

    return convexHull;
}

void QuickHull4D::findHull(vector<Point*> points, Point* P, Point* Q, Point* R, Point* S){
    Point* C;
    vector<Point*> S1, S2, S3, S4;
    cout<<"Qtd points: "<<points.size()<<endl;
    cout<<"\t Plane point: ";
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<P->getCord()[i]<<(i!=3?",":") ");
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<Q->getCord()[i]<<(i!=3?",":") ");
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<R->getCord()[i]<<(i!=3?",":") ");
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<S->getCord()[i]<<(i!=3?",":")\n");
    
        
    

    if(points.size()==0)
        return;

    pair<float,Point*> farthestPoint;
    farthestPoint.first = 0;
    farthestPoint.second = points[0];

    //---- Find farthest point to the line ----//
    // TODO calculate distance to hyperPlane
    for(auto point : points){
         // Calculate distance
         float dist;
         float volume4D = hyperVolume(P, Q, R, S, point);
         float volume3D = volume(P, Q, R, S);
         
         dist = volume4D/volume3D;

         if(farthestPoint.first<dist){
             farthestPoint.second = point;
             farthestPoint.first = dist;

         }
    }
    cout<<"\tFarthest: "<<farthestPoint.first<<endl;
    C = farthestPoint.second;
    convexHull.push_back(C);
    C->setColor(0,1,0);
    //---- Calculate subset 1 ----//
    /*for(auto point : _container->getPoints()){
        float position = (C->x() - P->x()) * (point->y() - P->y()) -
                        (C->y() - P->y()) * (point->x() - P->x());
        // On the line or to one side
        if(position>0){
            S1.push_back(point);
        }
    }
    //---- Calculate subset 2 ----//
    for(auto point : _container->getPoints()){
        float position = (Q->x() - C->x()) * (point->y() - C->y()) -
                        (Q->y() - C->y()) * (point->x() - C->x());
        // On the line or to one side
        if(position>0){
            S2.push_back(point);
        }
    }
    findHull(S1, P, C);
    findHull(S2, C, Q);*/
}

void QuickHull4D::draw(){
    /*if(convexHull.size()<2)
        return;

    // Set all points as black
    for(auto point : _container->getPoints()){
    point->setColor(0,0,0);
    }

    //----- Convex hull lines and points -----//
    sortConvexHull();
    if(convexHull.size()>1){
    glLineWidth(2);
    glColor3f(0.0, 0.0, 1.0);
    convexHull[0]->setColor(0,0,1);
    for (unsigned int i = 1; i < convexHull.size(); i++) {
      convexHull[i]->setColor(0,0,1);
      glBegin(GL_LINES);
      glVertex3f(convexHull[i]->x(), convexHull[i]->y(), 0.0);
      glVertex3f(convexHull[i-1]->x(), convexHull[i-1]->y(), 0.0);
      glEnd();
    }
    glBegin(GL_LINES);
    glVertex3f(convexHull.back()->x(), convexHull.back()->y(), 0.0);
    glVertex3f(convexHull.front()->x(), convexHull.front()->y(), 0.0);
    glEnd();
    }

    //----- First points -----//
    firstPointsA->setColor(1,0,0);
    firstPointsB->setColor(1,0,0);*/
}

void QuickHull4D::sortConvexHull(){
    /*vector<pair<float,Point*>> sortedAngles;
    vector<Point*> sortedPoints;

    for(auto point : convexHull){
        float angle = atan2(convexHull[0]->y()-point->y(),(convexHull[0]->x()-point->x()));
        sortedAngles.push_back(make_pair(angle, point));
    }
    sort(sortedAngles.begin(), sortedAngles.end());

    convexHull.clear();
    for(auto pointPair : sortedAngles){
      convexHull.push_back(pointPair.second);
    }*/
}

float QuickHull4D::hyperVolume(Point* t1, Point* t2, Point* t3, Point* t4, Point* t5){
    float det;
    float matrix[5][5];
    for(int i=0;i<4;i++){
        matrix[i][0] = t1->getCord()[i];
        matrix[i][1] = t2->getCord()[i];
        matrix[i][2] = t3->getCord()[i];
        matrix[i][3] = t4->getCord()[i];
        matrix[i][4] = t5->getCord()[i];
    }
    for(int i=0;i<5;i++){
        matrix[4][i] = 1;
    }

    // | p1x p2x p3x p4x p5x |
    // | p1y p2y p3y p4y p5y |
    // | p1z p2z p3z p4z p5z |
    // | p1w p2w p3w p4w p5w |
    // |  1   1   1   1   1  |

    // Determinant calculation
    det = determinant(matrix, 5);
    return 1.0f/24 * det;// 4! = 24
}

float QuickHull4D::volume(Point* t1, Point* t2, Point* t3, Point* t4){
    float det;
    float matrix[5][5];
    for(int i=0;i<3;i++){
        matrix[i][0] = t1->getCord()[i];
        matrix[i][1] = t2->getCord()[i];
        matrix[i][2] = t3->getCord()[i];
        matrix[i][3] = t4->getCord()[i];
    }
    for(int i=0;i<4;i++){
        matrix[3][i] = 1;
    }
    // | p1x p2x p3x p4x |
    // | p1y p2y p3y p4y |
    // | p1z p2z p3z p4z |
    // |  1   1   1   1  |

    // Determinant calculation
    det = determinant(matrix, 4);

    return 1.0f/6 * det;// 3! = 6
}

float QuickHull4D::determinant(float matrix[5][5], int n) {
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
