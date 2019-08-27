all: build

build: point.o container.o main.o

main.o: main.cpp
	@g++ main.cpp -Wall -o run -lglut -lGLU -lGL container.o point.o

container.o: classes/container.cpp classes/container.h
	@g++ classes/container.cpp -Wall -c -lglut -lGLU -lGL -std=c++11 point.o

point.o: classes/point.cpp classes/point.h
	@g++ classes/point.cpp -Wall -c -lglut -lGLU -lGL -std=c++11

clean:
	@rm run *.o
