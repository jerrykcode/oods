CC = g++
TARGET = TarjanMain

GRAPH_PATH = ../
INCLUDE = -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

DEPS = Tarjan.h
OBJS = Tarjan.o TarjanMain.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

Tarjan.o : $(DEPS) Tarjan.cpp
	$(CC) -c Tarjan.cpp $(CXXFLAGS)

TarjanMain.o : TarjanMain.cpp
	$(CC) -c TarjanMain.cpp $(CXXFLAGS)

