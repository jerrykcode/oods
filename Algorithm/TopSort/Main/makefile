CC = g++
TARGET = topsort

TOPSORT_PATH = ..
GRAPH_PATH = ../../../Graph

INCLUDE = -I$(TOPSORT_PATH) -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

DEPS = $(TOPSORT_PATH)/* $(GRAPH_PATH)/*

$(TARGET) : $(DEPS) main.cpp
	$(CC) -o $(TARGET) main.cpp $(CXXFLAGS)
