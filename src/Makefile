flags = -Wall -lglut -lGLU -lGL -std=c++11

all: build

build: point.o utils.o container.o convexHull.o main.o

main.o: main.cpp
	@g++ main.cpp $(flags) -o run  convexHull.o container.o point.o utils.o

convexHull.o: classes/convexHull.cpp classes/convexHull.h
	@g++ classes/convexHull.cpp $(flags) -c

container.o: classes/container.cpp classes/container.h
	@g++ classes/container.cpp $(flags) -c

utils.o: classes/utils.cpp classes/utils.h
	@g++ classes/utils.cpp $(flags) -c

point.o: classes/point.cpp classes/point.h
	@g++ classes/point.cpp $(flags) -c

clean:
	@rm run *.o
