Flags = -Wall -lglut -lGLU -lGL -std=c++11
Objects = point.o utils.o container.o convexHull.o graham.o quickHull2D.o quickHull4D.o

all: build

build: $(Objects) main.o

main.o: main.cpp
	@g++ main.cpp $(Flags) -o run $(Objects)

quickHull4D.o: classes/convexHull/quickHull4D.cpp classes/convexHull/quickHull4D.h
	@g++ classes/convexHull/quickHull4D.cpp $(Flags) -c

quickHull2D.o: classes/convexHull/quickHull2D.cpp classes/convexHull/quickHull2D.h
	@g++ classes/convexHull/quickHull2D.cpp $(Flags) -c

graham.o: classes/convexHull/graham.cpp classes/convexHull/graham.h
	@g++ classes/convexHull/graham.cpp $(Flags) -c

convexHull.o: classes/convexHull/convexHull.cpp classes/convexHull/convexHull.h
	@g++ classes/convexHull/convexHull.cpp $(Flags) -c

container.o: classes/container.cpp classes/container.h
	@g++ classes/container.cpp $(Flags) -c

utils.o: classes/utils.cpp classes/utils.h
	@g++ classes/utils.cpp $(Flags) -c

point.o: classes/point.cpp classes/point.h
	@g++ classes/point.cpp $(Flags) -c

clean:
	@rm run *.o
