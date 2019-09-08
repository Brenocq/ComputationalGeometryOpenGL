# ComputationalGeometryOpenGL
In this project I am testing some concepts of computational geometry using OpenGL for visualization. This repository came from the discipline "SCC0910 - Advanced Topics in Computer Science", taught the professor Phan Thanh An.

## ConvexHull

### Graham Algorithm
<p align="center">
<img src="https://raw.githubusercontent.com/Brenocq/ComputationalGeometryOpenGL/master/img/ConvexHullGraham.png" height=300></img>
</p>

Some questions proposed by Phan Thanh An:
1. What happens if you replace “lowest”by ”highest”?

  There is no difference Convex Hull formed. The chosen point will belong to Convex Hull and the search direction of the other points will continue counterclockwise.

  <p align="center">
  <img src="https://raw.githubusercontent.com/Brenocq/ComputationalGeometryOpenGL/master/img/ConvexHullGrahamHighestPoint.png" height=200></img>
  </p>

2. What happens if you replace “strictly left” by left”?

  In this case it may happen that the chosen starting point has the smallest possible Y coordinate between the points, but does not have the smallest / largest X possible among all points with this smallest Y coordinate. In this situation, the formed Convex Hull is correct, but will not be Convex Hull with as few points as possible.

3. What happens if you replace “rightmost lowest point” by “a point in the interior of the convex hull”?

  The Convex Hull formed by the algorithm will not be correct because it will have a point (the initial) that will not belong to the true Convex Hull.

  <p align="center">
  <img src="https://raw.githubusercontent.com/Brenocq/ComputationalGeometryOpenGL/master/img/ConvexHullGrahamPointInside.png" height=200></img>
  </p>

The necessary code modifications to test each case are in `src/classes/convexHull/graham.cpp` (_getFirstPoint_ method)
