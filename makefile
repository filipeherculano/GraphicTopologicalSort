CC=g++
CFLAGS=-std=c++11 -Wfatal-errors -lglut -lGLU -lGL

object: src/building.cpp src/edges.cpp src/graph.cpp src/ambient.cpp main.cpp
	$(CC) -o object src/*.cpp main.cpp $(CFLAGS) && ./object
