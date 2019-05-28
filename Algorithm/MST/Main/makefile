CC = g++
TARGET = mst

MST_PATH = ..
GRAPH_PATH = ../../../Graph
INCLUDE = -I$(MST_PATH) -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

DEPS = $(MST_PATH)/* $(GRAPH_PATH)/*

$(TARGET) :  $(DEPS)
	$(CC) -o $(TARGET) main.cpp $(CXXFLAGS)
