# makefile
# make SSSP

CC = g++

TARGET = SSSP

# path for SSSP
SSSP_PATH = ..

# path for graph
GRAPH_PATH = ../../../Graph

INCLUDE = -I$(SSSP_PATH) -I$(GRAPH_PATH)

CXXFLAGS = $(INCLUDE)

OBJ = pathRecorder.o main.o

# make target SSSP
$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET).exe $(OBJ) $(CXXFLAGS)

# make pathRecorder.o
PATH_RECORDER = $(SSSP_PATH)/pathRecorder.h $(SSSP_PATH)/pathRecorder.cpp $(GRAPH_PATH)/Vertex.h

pathRecorder.o : $(PATH_RECORDER)
	$(CC) -c $(SSSP_PATH)/pathRecorder.cpp $(CXXFLAGS)


# make main.o
MAIN = $(SSSP_PATH)/dijkstra.h $(SSSP_PATH)/astar.h $(GRAPH_PATH)/GraphInput.h main.cpp

main.o : $(MAIN)
	$(CC) -c main.cpp $(CXXFLAGS)
