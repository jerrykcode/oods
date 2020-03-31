#include "gtest/gtest.h"
#include "dijkstra.h"
#include "optimized_dijkstra.h"
#include "list_w_graph.h"
#include "matrix_w_graph.h"
#include "testequalpath.h"

//Edge weight
struct EW {
    short cost;
    short time;
    EW(short s) : cost(s), time(s) { }
    EW(short cost, short time) : cost(cost), time(time) {}
    bool operator <(const short s);
};

//Dist weight
struct DW {
    int cost;
    int time;

    DW() {}
    DW(int i) : cost(i), time(i) { }
    DW(int cost, int time) : cost(cost), time(time) { }

    DW operator +(EW ew);
    bool operator <(DW dw);
    bool operator >(DW dw);
    bool operator ==(DW dw);
};

class CompareWeight {
public:
    virtual bool CompareEW_Short(EW * a, short s) = 0;
    virtual bool CompareDW(DW * a, DW * b) = 0;
    virtual bool EqualDW(DW * a, DW * b) = 0;
};
CompareWeight * _p_compare_;

class CompareCost : public CompareWeight {
public:
    virtual bool CompareEW_Short(EW * a, short s) {
        return a->cost > s;
    }

    virtual bool CompareDW(DW * a, DW * b) {
        return a->cost > b->cost;
    }

    virtual bool EqualDW(DW * a, DW * b) {
        return a->cost == b->cost;
    }
};

class CompareTime : public CompareWeight {
public:
    virtual bool CompareEW_Short(EW * a, short s) {
        return a->time > s;
    }

    virtual bool CompareDW(DW * a, DW * b) {
        return a->time > b->time;
    }

    virtual bool EqualDW(DW * a, DW * b) {
        return a->time == b->time;
    }
};

class CompareCostFirst : public CompareWeight {
public:
    virtual bool CompareEW_Short(EW * a, short s) {
        return a->cost > s && a->time > s;
    }

    virtual bool CompareDW(DW * a, DW * b) {
        return a->cost != b->cost ? a->cost > b->cost : a->time > b->time;
    }

    virtual bool EqualDW(DW * a, DW * b) {
        return a->cost == b->cost && a->time == b->time;
    }
};

bool EW::operator <(const short s) {
    return !_p_compare_->CompareEW_Short(this, s);
}

DW DW::operator +(EW ew) {
     return DW(cost + (int)ew.cost, time + (int)ew.time);
}

bool DW::operator <(DW dw) {
    return _p_compare_->CompareDW(&dw, this);
}

bool DW::operator >(DW dw) {
    return _p_compare_->CompareDW(this, &dw);
}

bool DW::operator ==(DW dw) {
    return _p_compare_->EqualDW(this, &dw);
}

void AddWEdge(WGraph<EW> * p_graph, Vertex v, Vertex w, short cost, short time) {
    Edge * p_edge = new WEdge<struct EW>(v, w, EW(cost, time));
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

// p_graph 
void TestSssp(Sssp<struct EW, struct DW> * p_sssp, WGraph<struct EW>* p_graph) {
    AddWEdge(p_graph, 0, 1, 1, 5);
    AddWEdge(p_graph, 0, 2, 10, 6);
    AddWEdge(p_graph, 0, 4, 3, 6);
    AddWEdge(p_graph, 1, 3, 2, 3);
    AddWEdge(p_graph, 3, 2, 2, 2);
    AddWEdge(p_graph, 4, 2, 2, 7);
    
    EXPECT_EQ(p_graph->GetEdgeWeight(2, 4).time, 7);

    _p_compare_ = new CompareCost();
    PathRecorder * p_recorder = new AllPathsRecorder(5);
    vector<Path *>paths;
    DW dist;
    bool result;


    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 2, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist.cost, 5);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(0, 2, paths);
    std::sort(paths.begin(), paths.end(), ComparePath);
    EXPECT_EQ(paths.size(), 2);
    TestEqualPath(paths[0], {0, 1, 3, 2});
    TestEqualPath(paths[1], {0, 4, 2});
    DeletePaths(paths);
    
    delete _p_compare_;
    _p_compare_ = new CompareTime();
    p_recorder->Clear();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 2, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist.time, 6);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(0, 2, paths);
    EXPECT_EQ(paths.size(), 1);
    TestEqualPath(paths[0], {0, 2});
    DeletePaths(paths);
    
    delete _p_compare_;
    _p_compare_ = new CompareCostFirst();
    p_recorder->Clear();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 2, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist.cost, 5);
    EXPECT_EQ(dist.time, 10);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(0, 2, paths);
    EXPECT_EQ(paths.size(), 1);
    TestEqualPath(paths[0], {0, 1, 3, 2});
    DeletePaths(paths);

    p_graph->SetEdgeWeight(2, 4, EW(2, 4));
    EXPECT_EQ(p_graph->GetEdgeWeight(2, 4).time, 4);

     delete _p_compare_;
    _p_compare_ = new CompareCostFirst();
    p_recorder->Clear();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 2, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist.cost, 5);
    EXPECT_EQ(dist.time, 10);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(0, 2, paths);
    EXPECT_EQ(paths.size(), 2);
    std::sort(paths.begin(), paths.end(), ComparePath);
    TestEqualPath(paths[0], {0, 1, 3, 2});
    TestEqualPath(paths[1], {0, 4, 2});
    DeletePaths(paths);


    delete _p_compare_;
    delete p_recorder;
}

TEST(Sssp, dijkstra_multiple_edgeweight) {
    Sssp<struct EW, struct DW> * p_sssp = new HeapOptimizedDijkstra<struct EW, struct DW>();
    WGraph<struct EW> * p_graph = new ListWGraph<struct EW>(5, false);
    TestSssp(p_sssp, p_graph);
    delete p_sssp;
    delete p_graph;
}


