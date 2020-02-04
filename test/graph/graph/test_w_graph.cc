#include "gtest/gtest.h"
#include "list_w_graph.h"
#include "matrix_w_graph.h"
using namespace oods::oograph;

template<typename EdgeWeight>
void AddWEdge(Graph * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
    Edge * p_edge = new WEdge<EdgeWeight>(v, w, edge_weight);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

template<typename EdgeWeight>
void testWGraph(WGraph<EdgeWeight> * p_graph, bool is_directed) {
    AddWEdge<EdgeWeight>(p_graph, 0, 1, 2);
    AddWEdge<EdgeWeight>(p_graph, 0, 3, 3);
    AddWEdge<EdgeWeight>(p_graph, 1, 4, 1);
    AddWEdge<EdgeWeight>(p_graph, 3, 2, 1);
    AddWEdge<EdgeWeight>(p_graph, 3, 4, 6);
    AddWEdge<EdgeWeight>(p_graph, 2, 4, 5);    
   
    EXPECT_EQ(p_graph->GetNumVertices(), 5);
    ASSERT_TRUE(p_graph->IsWeighted());


    ASSERT_TRUE(p_graph->HasEdge(0, 1));
    ASSERT_TRUE(p_graph->HasEdge(0, 3));
    ASSERT_TRUE(p_graph->HasEdge(1, 4));
    ASSERT_TRUE(p_graph->HasEdge(3, 2));
    ASSERT_TRUE(p_graph->HasEdge(3, 4));
    ASSERT_TRUE(p_graph->HasEdge(2, 4));

    ASSERT_FALSE(p_graph->HasEdge(0, 4));
    ASSERT_FALSE(p_graph->HasEdge(3, 1));

    EXPECT_EQ(p_graph->GetEdgeWeight(0, 1), 2);
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 3), 3);
    EXPECT_EQ(p_graph->GetEdgeWeight(1, 4), 1);
    EXPECT_EQ(p_graph->GetEdgeWeight(3, 2), 1);
    EXPECT_EQ(p_graph->GetEdgeWeight(3, 4), 6);
    EXPECT_EQ(p_graph->GetEdgeWeight(2, 4), 5);    
    
    if (is_directed) {
        ASSERT_TRUE(p_graph->IsDirected());
        EXPECT_EQ(p_graph->GetNumEdges(), 6);
    }
    else {
        ASSERT_FALSE(p_graph->IsDirected());
        
        ASSERT_TRUE(p_graph->HasEdge(1, 0));
        ASSERT_TRUE(p_graph->HasEdge(3, 0));
        ASSERT_TRUE(p_graph->HasEdge(4, 1));
        ASSERT_TRUE(p_graph->HasEdge(2, 3));
        ASSERT_TRUE(p_graph->HasEdge(4, 3));
        ASSERT_TRUE(p_graph->HasEdge(4, 2));


        EXPECT_EQ(p_graph->GetNumEdges(), 12);
        EXPECT_EQ(p_graph->GetEdgeWeight(1, 0), 2);
        EXPECT_EQ(p_graph->GetEdgeWeight(3, 0), 3);
        EXPECT_EQ(p_graph->GetEdgeWeight(4, 1), 1);
        EXPECT_EQ(p_graph->GetEdgeWeight(2, 3), 1);
        EXPECT_EQ(p_graph->GetEdgeWeight(4, 3), 6);
        EXPECT_EQ(p_graph->GetEdgeWeight(4, 2), 5);
    }
 
    p_graph->SetEdgeWeight(0, 1, 4);
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 1), 4);
    if (!is_directed) {
        EXPECT_EQ(p_graph->GetEdgeWeight(1, 0), 4);
    }
    p_graph->AddVertex();
    EXPECT_EQ(p_graph->GetNumVertices(), 6);
    AddWEdge<int>(p_graph, 2, 5, 3);
    EXPECT_EQ(p_graph->GetEdgeWeight(2, 5), 3);
    
    if (is_directed) {
        EXPECT_EQ(p_graph->GetNumEdges(), 7);
    }
    else {
        EXPECT_EQ(p_graph->GetNumEdges(), 14);
    }

    p_graph->RemoveEdge(3, 2);
    ASSERT_FALSE(p_graph->HasEdge(3, 2));
    if (!is_directed) {
        ASSERT_FALSE(p_graph->HasEdge(2, 3));
    }

    if (is_directed) {
        EXPECT_EQ(p_graph->GetNumEdges(), 6);
    }
    else {
        EXPECT_EQ(p_graph->GetNumEdges(), 12);
    }
}

TEST(WGraph, list_w_graph) {
    Graph * p_graph = new ListWGraph<int>(5, true);
    testWGraph<int>((WGraph<int>*)p_graph, true);
    delete p_graph;

    p_graph = new ListWGraph<int>(5, false); 
    testWGraph<int>((WGraph<int>*)p_graph, false);
    delete p_graph;

    p_graph = new ListWGraph<unsigned char>(5, true);
    testWGraph<unsigned char>((WGraph<unsigned char>*)p_graph, true);
    delete p_graph;

    p_graph = new ListWGraph<unsigned char>(5, false);
    testWGraph<unsigned char>((WGraph<unsigned char>*)p_graph, false);
    delete p_graph;
}

TEST(WGraph, matrix_w_graph) {
    Graph * p_graph = new MatrixWGraph<int>(5, true);
    testWGraph<int>((WGraph<int>*)p_graph, true);
    delete p_graph;

    p_graph = new MatrixWGraph<int>(5, false); 
    testWGraph<int>((WGraph<int>*)p_graph, false);
    delete p_graph;

    p_graph = new MatrixWGraph<unsigned char>(5, true);
    testWGraph<unsigned char>((WGraph<unsigned char>*)p_graph, true);
    delete p_graph;

    p_graph = new MatrixWGraph<unsigned char>(5, false);
    testWGraph<unsigned char>((WGraph<unsigned char>*)p_graph, false);
    delete p_graph;
}

template<typename EdgeWeight>
void testWGraph2(WGraph<EdgeWeight> * p_graph, bool is_directed) {
    EXPECT_EQ(p_graph->GetNumVertices(), 10);
    ASSERT_TRUE(p_graph->IsWeighted());
    AddWEdge<EdgeWeight>(p_graph, 0, 1, 20);
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 1), 20);
    p_graph->SetEdgeWeight(0, 1, 120);
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 1), 120);
    AddWEdge<EdgeWeight>(p_graph, 1, 2, 3);
    AddWEdge<EdgeWeight>(p_graph, 1, 6, 70);
    AddWEdge<EdgeWeight>(p_graph, 1, 8, 24);
    AddWEdge<EdgeWeight>(p_graph, 2, 3, 78);
    AddWEdge<EdgeWeight>(p_graph, 2, 4, -9);
    AddWEdge<EdgeWeight>(p_graph, 3, 1, 23);
    AddWEdge<EdgeWeight>(p_graph, 3, 6, -11);
    AddWEdge<EdgeWeight>(p_graph, 4, 1, 100000);
    AddWEdge<EdgeWeight>(p_graph, 0, 9, 0x7fffffff);
    AddWEdge<EdgeWeight>(p_graph, 0, 2, -768);
    AddWEdge<EdgeWeight>(p_graph, 6, 5, 98);
    AddWEdge<EdgeWeight>(p_graph, 6, 7, -11111111);
    AddWEdge<EdgeWeight>(p_graph, 7, 4, 20);
    AddWEdge<EdgeWeight>(p_graph, 8, 9, 89);
    AddWEdge<EdgeWeight>(p_graph, 9, 6, -90);
    AddWEdge<EdgeWeight>(p_graph, 5, 8, 1);
    AddWEdge<EdgeWeight>(p_graph, 7, 2, 0);
    AddWEdge<EdgeWeight>(p_graph, 3, 9, 0);
    AddWEdge<EdgeWeight>(p_graph, 1, 9, 0);
    AddWEdge<EdgeWeight>(p_graph, 8, 4, 2000);
    
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 1), 120);
    EXPECT_EQ(p_graph->GetEdgeWeight(1, 2), 3);
    EXPECT_EQ(p_graph->GetEdgeWeight(1, 6), 70);
    EXPECT_EQ(p_graph->GetEdgeWeight(1, 8), 24);
    EXPECT_EQ(p_graph->GetEdgeWeight(2, 3), 78);
    EXPECT_EQ(p_graph->GetEdgeWeight(2, 4), -9);
    EXPECT_EQ(p_graph->GetEdgeWeight(3, 1), 23);
    EXPECT_EQ(p_graph->GetEdgeWeight(3, 6), -11);
    EXPECT_EQ(p_graph->GetEdgeWeight(4, 1), 100000);
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 9), 0x7fffffff);
    EXPECT_EQ(p_graph->GetEdgeWeight(0, 2), -768);
    EXPECT_EQ(p_graph->GetEdgeWeight(6, 5), 98);
    EXPECT_EQ(p_graph->GetEdgeWeight(6, 7), -11111111);
    EXPECT_EQ(p_graph->GetEdgeWeight(7, 4), 20);
    EXPECT_EQ(p_graph->GetEdgeWeight(8, 9), 89);
    EXPECT_EQ(p_graph->GetEdgeWeight(9, 6), -90);
    EXPECT_EQ(p_graph->GetEdgeWeight(5, 8), 1);
    EXPECT_EQ(p_graph->GetEdgeWeight(7, 2), 0);
    EXPECT_EQ(p_graph->GetEdgeWeight(3, 9), 0);
    EXPECT_EQ(p_graph->GetEdgeWeight(1, 9), 0);
    EXPECT_EQ(p_graph->GetEdgeWeight(8, 4), 2000);

    if (is_directed) {
        ASSERT_TRUE(p_graph->IsDirected());
        
        EXPECT_EQ(p_graph->GetNumEdges(), 21);
    }
    else {
        ASSERT_FALSE(p_graph->IsDirected());
        EXPECT_EQ(p_graph->GetEdgeWeight(1, 0), 120);
        EXPECT_EQ(p_graph->GetEdgeWeight(2, 1), 3);
        EXPECT_EQ(p_graph->GetEdgeWeight(6, 1), 70);
        EXPECT_EQ(p_graph->GetEdgeWeight(8, 1), 24);
        EXPECT_EQ(p_graph->GetEdgeWeight(3, 2), 78);
        EXPECT_EQ(p_graph->GetEdgeWeight(4, 2), -9);
        EXPECT_EQ(p_graph->GetEdgeWeight(1, 3), 23);
        EXPECT_EQ(p_graph->GetEdgeWeight(6, 3), -11);
        EXPECT_EQ(p_graph->GetEdgeWeight(1, 4), 100000);
        EXPECT_EQ(p_graph->GetEdgeWeight(9, 0), 0x7fffffff);
        EXPECT_EQ(p_graph->GetEdgeWeight(2, 0), -768);
        EXPECT_EQ(p_graph->GetEdgeWeight(5, 6), 98);
        EXPECT_EQ(p_graph->GetEdgeWeight(7, 6), -11111111);
        EXPECT_EQ(p_graph->GetEdgeWeight(4, 7), 20);
        EXPECT_EQ(p_graph->GetEdgeWeight(9, 8), 89);
        EXPECT_EQ(p_graph->GetEdgeWeight(6, 9), -90);
        EXPECT_EQ(p_graph->GetEdgeWeight(8, 5), 1);
        EXPECT_EQ(p_graph->GetEdgeWeight(2, 7), 0);
        EXPECT_EQ(p_graph->GetEdgeWeight(9, 3), 0);
        EXPECT_EQ(p_graph->GetEdgeWeight(9, 1), 0);
        EXPECT_EQ(p_graph->GetEdgeWeight(4, 8), 2000);

        EXPECT_EQ(p_graph->GetNumEdges(), 42);
    }
}


TEST(WGraph, list_w_graph2) {
    Graph * p_graph = new ListWGraph<int>(10, true);
    testWGraph2<int>((WGraph<int>*)p_graph, true);
    delete p_graph;

    p_graph = new ListWGraph<int>(10, false); 
    testWGraph2<int>((WGraph<int>*)p_graph, false);
    delete p_graph;

    p_graph = new ListWGraph<long long>(10, true);
    testWGraph2<long long>((WGraph<long long>*)p_graph, true);
    delete p_graph;

    p_graph = new ListWGraph<long long>(10, false);
    testWGraph2<long long>((WGraph<long long>*)p_graph, false);
    delete p_graph;
}

TEST(WGraph, matrix_w_graph2) {
    Graph * p_graph = new MatrixWGraph<int>(10, true);
    testWGraph2<int>((WGraph<int>*)p_graph, true);
    delete p_graph;

    p_graph = new MatrixWGraph<int>(10, false); 
    testWGraph2<int>((WGraph<int>*)p_graph, false);
    delete p_graph;

    p_graph = new MatrixWGraph<long long>(10, true);
    testWGraph2<long long>((WGraph<long long>*)p_graph, true);
    delete p_graph;

    p_graph = new MatrixWGraph<long long>(10, false);
    testWGraph2<long long>((WGraph<long long>*)p_graph, false);
    delete p_graph;
}
