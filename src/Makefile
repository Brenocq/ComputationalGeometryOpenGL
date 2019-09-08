Flags = -Wall -lglut -lGLU -lGL -std=c++11
Objects = point.o utils.o container.o convexHull.o graham.o quickHull.o

all: build

build: $(Objects) main.o

main.o: main.cpp
	@g++ main.cpp $(Flags) -o run $(Objects)

quickHull.o: classes/convexHull/quickHull.cpp classes/convexHull/quickHull.h
	@g++ classes/convexHull/quickHull.cpp $(Flags) -c

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
