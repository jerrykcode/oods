CC = g++
TARGET = mf

MF_PATH = ..
GRAPH_PATH = ../../../Graph

INCLUDE = -I$(MF_PATH) -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

DEPS = $(MF_PATH)/* $(GRAPH_PATH)/*

$(TARGET) : $(DEPS) main.cpp
	$(CC) -o $(TARGET) main.cpp $(CXXFLAGS)
