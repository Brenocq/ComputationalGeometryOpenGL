#include "quickHull2D.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include "../utils.h"

QuickHull2D::QuickHull2D():
ConvexHull()
{}

QuickHull2D::~QuickHull2D()
{}

vector<Point*> QuickHull2D::run(){
    vector<Point*> S1, S2;
    Point *leftMost, *rightMost;
    convexHull.clear();

    if(_container->getPoints().size()<2)
        return convexHull;

    //----- Find left and right most points -----//
    leftMost = _container->getPoints()[0];
    rightMost = _container->getPoints()[0];
    for(auto point : _container->getPoints()){
        if(point->x()<leftMost->x())
            leftMost = point;
        else if(point->x()>rightMost->x())
            rightMost = point;
    }
    convexHull.push_back(leftMost);
    convexHull.push_back(rightMost);
    firstPointsA = leftMost;// To draw
    firstPointsB = rightMost;// To draw

    //----- Divide points in two subsets -----//

    for(auto point : _container->getPoints()){
        float position = (rightMost->x() - leftMost->x()) * (point->y() - leftMost->y()) -
                        (rightMost->y() - leftMost->y()) * (point->x() - leftMost->x());
        // On the line or to one side
        if(position>0){
            S1.push_back(point);
        }else if(position<0){
            S2.push_back(point);
        }
    }
    //----- Divide points in two subsets -----//

    findHull(S1, leftMost, rightMost);
    findHull(S2, rightMost, leftMost);

    return convexHull;
}

void QuickHull2D::findHull(vector<Point*> points, Point* P, Point* Q){
    Point* C;
    vector<Point*> S1, S2;
    if(points.size()==0)
        return;

    pair<float,Point*> farthestPoint;
    farthestPoint.first = 0;
    farthestPoint.second = points[0];

    //---- Find farthest point to the line ----//
    for(auto point : points){
         // Calculate distance
         float a,b,c, dist;
         a = P->y() - Q->y();
         b = Q->x() - P->x();
         c = P->x() * Q->y() - Q->x() * P->y();
         dist = abs(a * point->x() + b * point->y() + c) / sqrt(a * a + b * b);

         if(farthestPoint.first<dist){
             farthestPoint.second = point;
             farthestPoint.first = dist;

         }
    }
    C = farthestPoint.second;
    convexHull.push_back(C);
    //---- Calculate subset 1 ----//
    for(auto point : _container->getPoints()){
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
    findHull(S2, C, Q);
}

void QuickHull2D::draw(){
    if(convexHull.size()<2)
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
    firstPointsB->setColor(1,0,0);
}

void QuickHull2D::sortConvexHull(){
    vector<pair<float,Point*>> sortedAngles;
    vector<Point*> sortedPoints;

    for(auto point : convexHull){
        float angle = atan2(convexHull[0]->y()-point->y(),(convexHull[0]->x()-point->x()));
        sortedAngles.push_back(make_pair(angle, point));
    }
    sort(sortedAngles.begin(), sortedAngles.end());

    convexHull.clear();
    for(auto pointPair : sortedAngles){
      convexHull.push_back(pointPair.second);
    }
}
