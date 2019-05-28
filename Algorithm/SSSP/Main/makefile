# makefile
# make sssp 

CC = g++

TARGET = sssp 

# path for SSSP
SSSP_PATH = ..

# path for graph
GRAPH_PATH = ../../../Graph

INCLUDE = -I$(SSSP_PATH) -I$(GRAPH_PATH)
CXXFLAGS = $(INCLUDE)

DEPS = $(SSSP_PATH)/* $(GRAPH_PATH)/*

OBJ = pathRecorder.o main.o

# make target SSSP
$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CXXFLAGS)

# make pathRecorder.o
PATH_RECORDER = $(SSSP_PATH)/pathRecorder.h $(SSSP_PATH)/pathRecorder.cpp $(GRAPH_PATH)/Vertex.h

pathRecorder.o : $(PATH_RECORDER)
	$(CC) -c $(SSSP_PATH)/pathRecorder.cpp $(CXXFLAGS)


# make main.o

main.o : $(DEPS)
	$(CC) -c main.cpp $(CXXFLAGS)
