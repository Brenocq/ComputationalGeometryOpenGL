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

    cout<<"\tFirst points: ";
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
            cout<<(i==0?"(":"")<<p[j]->getCord()[i]<<(i!=3?",":") ");
    }
    cout<<endl;

    //----- Divide points in two subsets -----//
    for(auto point : _container->getPoints()){
        float position = volume(vector<Point*>{firstPoints[0], firstPoints[1], firstPoints[2], firstPoints[3], point});
        
        cout<<"Volume with ";
        for (int i = 0; i < 4; i++)
            cout<<(i==0?"(":"")<<point->getCord()[i]<<(i!=3?",":") ");
        cout<<"-> "<<position<<endl;


        // On the line or to one side
        if(position>0 && abs(position)>0.0001){
            S1.push_back(point);
        }else if(position<0 && abs(position)>0.0001){
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
    cout<<"-------------\nQtd points: "<<points.size()<<endl;
    cout<<"\tPlane point: ";
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<P->getCord()[i]<<(i!=3?",":") ");
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<Q->getCord()[i]<<(i!=3?",":") ");
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<R->getCord()[i]<<(i!=3?",":") ");
    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<S->getCord()[i]<<(i!=3?",":")\n");
    
    cout<<"\tPoints Added: ";
    for(Point* point : points){
        for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<point->getCord()[i]<<(i!=3?",":") ");
    }
    cout<<endl;
    

    /*if(points.size()==0)
        return;

    pair<float,Point*> farthestPoint;
    farthestPoint.first = 0;
    farthestPoint.second = points[0];

    //---- Find farthest point to the line ----//
    // TODO calculate distance to hyperPlane
    for(auto point : points){
         // Calculate distance
         float dist;
         float volume4D = volume(vector<Point*>{P, Q, R, S, point});
         float volume3D = volume(vector<Point*>{P, Q, R, S});
         
         dist = volume4D/volume3D;

         if(abs(farthestPoint.first)<abs(dist)){
             farthestPoint.second = point;
             farthestPoint.first = dist;

         }
    }
    cout<<"\tFarthest: ";

    for (int i = 0; i < 4; i++)
        cout<<(i==0?"(":"")<<farthestPoint.second->getCord()[i]<<(i!=3?",":")");

    cout<<" -> distance plane:"<<farthestPoint.first<<endl;
    C = farthestPoint.second;
    convexHull.push_back(C);
    C->setColor(0,1,0);
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

float QuickHull4D::volume(vector<Point*>p){
    // https://www.mathpages.com/home/kmath664/kmath664.html
    // Only works for 4d-simplex (4d points)

    float det;
    float matrix[5][5];

    int size  = p.size();

    for (int i = 0; i < size; i++)
    {
        matrix[i][0] = 1;
    }
    
    cout<<endl;
    for(int i=0;i<size;i++){
        for(int j=1;j<size;j++){
            matrix[i][j] = p[i]->getCord()[j-1];
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    // Print matrix
    cout<<endl;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    // Determinant calculation
    det = utils::determinant(matrix, 5);

}

bool QuickHull4D::pointInside(Point* t1, Point* t2, Point* t3, Point* t4, Point* t5, Point* p) {
    float baseVolume;
    float volumes[5]; //Volumes w.r.t. the point p
    
    std::vector<Point*> pointSet;
    std::vector<Point*> bufferSet;

    pointSet.push_back(t5);
    pointSet.push_back(t4);
    pointSet.push_back(t3);
    pointSet.push_back(t2);
    pointSet.push_back(t1);

    baseVolume = volume(vector<Point*>{t1, t2, t3, t4, t5});// Changed from hyperVolume to volume

    for (int i = 0; i < 4; i++) {
        bufferSet = pointSet; //Copying into bufferSet        
        bufferSet.at(i) =  p;
        volumes[i] = volume(vector<Point*>{
                                bufferSet.at(0),
                                bufferSet.at(1),
                                bufferSet.at(2),
                                bufferSet.at(3),
                                bufferSet.at(4)});
    }

}