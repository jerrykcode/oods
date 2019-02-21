CC = g++
TARGET = DijkstraMain

OBJ = Dijkstra.o DijkstraMain.o
GRAPH_PATH = ../
INCLUDE = -I$(GRAPH_PATH)
CFLAGS = $(INCLUDE)

# make TARGET
$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# make Dijkstra.o
Dijkstra.o : Dijkstra.h Dijkstra.cpp
	$(CC) -c Dijkstra.cpp $(CFLAGS) 

# make DijkstraMain.o
DijkstraMain.o : DijkstraMain.cpp
	$(CC) -c DijkstraMain.cpp $(CFLAGS)
