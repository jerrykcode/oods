#include "gtest/gtest.h"
#include "dijkstra.h"
#include "list_w_graph.h"
#include <algorithm>
using namespace oods::oograph;

template<typename EdgeWeight>
void AddWEdge(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
    Edge * p_edge = new WEdge<EdgeWeight>(v, w, edge_weight);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

void TestEqualPath(Path * p_path, std::initializer_list<Vertex> list) {
    vector<Vertex>& p_ref = p_path->GetPathRef();
    EXPECT_EQ(p_ref.size(), list.size());
    auto vi = p_ref.begin();
    auto li = list.begin();
    while (vi != p_ref.end()) {
        EXPECT_EQ(*vi, *li);
        vi++;
        li++;
    }
}

void TestSsspIntInt(Sssp<int, int> * p_sssp) {
    WGraph<int> * p_graph = new ListWGraph<int>(7, true);
    AddWEdge<int>(p_graph, 0, 1, 2);
    AddWEdge<int>(p_graph, 0, 2, 4);
    AddWEdge<int>(p_graph, 0, 6, 10);
    AddWEdge<int>(p_graph, 1, 2, 1);
    AddWEdge<int>(p_graph, 1, 5, 1);
    AddWEdge<int>(p_graph, 1, 6, 5);
    AddWEdge<int>(p_graph, 2, 3, 2);
    AddWEdge<int>(p_graph, 3, 4, 5);
    AddWEdge<int>(p_graph, 5, 6, 2);
    AddWEdge<int>(p_graph, 5, 4, 10);
    int dist;
    bool result;
    PathRecorder * p_recorder = new NoPathRecorder();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 4, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 10);
    p_recorder->Clear();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 6, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 5);
    delete p_recorder;
    p_recorder = (PathRecorder *)(new SinglePathRecorder(7));
    result = p_sssp->SingleSourceShortestPath(p_graph, 1, 4, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 8);
    Path * p_path = new Path();
    ((SinglePathRecorder *)p_recorder)->GetSinglePath(1, 4, p_path);
    TestEqualPath(p_path, {1, 2, 3, 4});
    delete p_path;
    delete p_recorder;
    delete p_graph;
}

bool ComparePath(Path * a, Path * b) {
    vector<Vertex>& a_ref = a->GetPathRef();
    vector<Vertex>& b_ref = b->GetPathRef();
    for (int i = 0; i < std::min(a_ref.size(), b_ref.size()); i++) {
        if (a_ref[i] < b_ref[i]) return true;
        if (a_ref[i] > b_ref[i]) return false;
        //if a_ref[i] == b_ref[i] then continue
    }
    return a_ref.size() < b_ref.size();
}

void DeletePaths(vector<Path *>& paths) {
    for (auto p_path : paths) {
        delete p_path;
    }
    paths.clear();
}

void TestSsspFloatFloat(Sssp<float, float> * p_sssp) {
    WGraph<float> * p_graph = new ListWGraph<float>(6, false);
    AddWEdge<float>(p_graph, 0, 1, 2);
    AddWEdge<float>(p_graph, 0, 3, 1);
    AddWEdge<float>(p_graph, 1, 2, 5);
    AddWEdge<float>(p_graph, 2, 3, 1);
    AddWEdge<float>(p_graph, 1, 4, 1);
    AddWEdge<float>(p_graph, 2, 4, 3);
    AddWEdge<float>(p_graph, 2, 5, 1.5);
    AddWEdge<float>(p_graph, 4, 5, 1.5);
    
    float dist;
    bool result;
    PathRecorder * p_recorder = new AllPathsRecorder(6);
    vector<Path *> paths;
    
    result = p_sssp->SingleSourceShortestPath(p_graph, 1, 2, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 4);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(1, 2, paths);
    EXPECT_EQ(paths.size(), 3);
    std::sort(paths.begin(), paths.end(), ComparePath);
    TestEqualPath(paths[0], {1, 0, 3, 2});
    TestEqualPath(paths[1], {1, 4, 2});
    TestEqualPath(paths[2], {1, 4, 5, 2});
    DeletePaths(paths);
    p_recorder->Clear();

    float * arr_dist = new float[p_graph->GetNumVertices()];
    result = p_sssp->SingleSourceMultipleGoalShortestPath(p_graph, 2, arr_dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(arr_dist[0], 2);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(2, 0, paths);
    EXPECT_EQ(paths.size(), 1);
    TestEqualPath(paths[0], {2, 3, 0});
    DeletePaths(paths);

    EXPECT_EQ(arr_dist[1], 4);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(2, 1, paths);
    EXPECT_EQ(paths.size(), 3);
    std::sort(paths.begin(), paths.end(), ComparePath);
    TestEqualPath(paths[0], {2, 3, 0, 1});
    TestEqualPath(paths[1], {2, 4, 1});
    TestEqualPath(paths[2], {2, 5, 4, 1});
    DeletePaths(paths);

    EXPECT_EQ(arr_dist[3], 1);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(2, 3, paths);
    EXPECT_EQ(paths.size(), 1);
    TestEqualPath(paths[0], {2, 3});
    DeletePaths(paths);

    EXPECT_EQ(arr_dist[4], 3);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(2, 4, paths);
    EXPECT_EQ(paths.size(), 2);
    std::sort(paths.begin(), paths.end(), ComparePath);
    TestEqualPath(paths[0], {2, 4});
    TestEqualPath(paths[1], {2, 5, 4});
    DeletePaths(paths);

    EXPECT_EQ(arr_dist[5], 1.5);
    ((AllPathsRecorder *)p_recorder)->GetAllPaths(2, 5, paths);
    EXPECT_EQ(paths.size(), 1);
    TestEqualPath(paths[0], {2, 5});
    DeletePaths(paths);

    free(arr_dist);
    delete p_recorder;
    delete p_graph;
}

TEST(Sssp, dijkstra) {
    Optimizer<int> * p_optimizer = new HeapOptimizer<int>();
    Sssp<int, int> * p_sssp = new Dijkstra<int, int>(p_optimizer);
    TestSsspIntInt(p_sssp);
    delete p_optimizer;
    delete p_sssp;
    p_optimizer = new NoOptimizer<int>();
    p_sssp = new Dijkstra<int, int>(p_optimizer);
    TestSsspIntInt(p_sssp);
    delete p_optimizer;
    delete p_sssp;
}

TEST(Sssp, dijkstra2) {
    Optimizer<float> * p_optimizer = new HeapOptimizer<float>();
    Sssp<float, float> * p_sssp = new Dijkstra<float, float>(p_optimizer);
    TestSsspFloatFloat(p_sssp);
    delete p_optimizer;
    delete p_sssp;
    p_optimizer = new NoOptimizer<float>();
    p_sssp = new Dijkstra<float, float>(p_optimizer);
    TestSsspFloatFloat(p_sssp);
    delete p_optimizer;
    delete p_sssp;
}
