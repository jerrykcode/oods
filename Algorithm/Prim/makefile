CC = g++
TARGET = PrimMain
OBJ = Prim.o PrimMain.o

$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

GRAPH_PATH = ../
INCLUDE = -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

Prim.o : Prim.h Prim.cpp
	$(CC) -c Prim.cpp $(CXXFLAGS)

PrimMain.o : PrimMain.cpp
	$(CC) -c PrimMain.cpp $(CXXFLAGS)
