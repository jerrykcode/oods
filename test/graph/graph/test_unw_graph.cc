#include "gtest/gtest.h"
#include "list_unw_graph.h"
using namespace oods::oograph;

void AddUnwEdge(Graph * p_graph, Vertex v, Vertex w) {
    Edge * p_edge = new UnwEdge(v, w);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

TEST(Graph, list_unw_graph) {
    Graph * p_graph = (Graph *)(new ListUnwGraph(7, true));
    AddUnwEdge(p_graph, 0, 1);
    AddUnwEdge(p_graph, 0, 2);
    AddUnwEdge(p_graph, 0, 3);
    AddUnwEdge(p_graph, 1, 2);
    AddUnwEdge(p_graph, 1, 3);
    AddUnwEdge(p_graph, 2, 5);
    AddUnwEdge(p_graph, 3, 1);
    AddUnwEdge(p_graph, 4, 5);
    AddUnwEdge(p_graph, 5, 6);
    AddUnwEdge(p_graph, 5, 1);
    ASSERT_TRUE(p_graph->HasEdge(0, 1));
    ASSERT_TRUE(p_graph->HasEdge(0, 2));
    ASSERT_TRUE(p_graph->HasEdge(0, 3));
    ASSERT_TRUE(p_graph->HasEdge(1, 2));
    ASSERT_TRUE(p_graph->HasEdge(1, 3));
    ASSERT_TRUE(p_graph->HasEdge(2, 5));
    ASSERT_TRUE(p_graph->HasEdge(3, 1));
    ASSERT_TRUE(p_graph->HasEdge(4, 5));
    ASSERT_TRUE(p_graph->HasEdge(5, 6));
    ASSERT_TRUE(p_graph->HasEdge(5, 1));
    ASSERT_FALSE(p_graph->HasEdge(0, 6));
    ASSERT_FALSE(p_graph->HasEdge(5, 2));
    EXPECT_EQ(p_graph->GetNumVertices(), 7);
    EXPECT_EQ(p_graph->GetNumEdges(), 10);
    p_graph->RemoveEdge(0, 1);
    p_graph->RemoveEdge(3, 1);
    EXPECT_EQ(p_graph->GetNumEdges(), 8);
    delete p_graph;
}
