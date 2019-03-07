CC = g++

TARGET = DijkstraMain

GRAPH_PATH = ../
INCLUDE = -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

DEPS = Dijkstra.h

$(TARGET) : $(DEPS) DijkstraMain.cpp
	$(CC) -o $(TARGET) DijkstraMain.cpp $(CXXFLAGS)
