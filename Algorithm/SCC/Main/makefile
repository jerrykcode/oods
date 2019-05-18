CC = g++
TARGET = scc

OBJ = tarjan.o main.o

SCC_PATH = ..
GRAPH_PATH = ../../../Graph

INCLUDE = -I$(SCC_PATH) -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

DEPS = $(SCC_PATH)/* $(GRAPH_PATH)/*

tarjan.o : $(DEPS)
	$(CC) -c $(SCC_PATH)/tarjan.cpp $(CXXFLAGS)


main.o : main.cpp $(DEPS)
	$(CC) -c main.cpp $(CXXFLAGS)
