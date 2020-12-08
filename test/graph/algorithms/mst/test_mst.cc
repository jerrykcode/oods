#include "gtest/gtest.h"
#include "test.h"
#include "addedge.h"

void TestMst(Mst<int, int> *p_mst, WGraphCreator<int> *p_creator) {
    WGraph<int> *p_graph = p_creator->CreateWGraph(6, false);
    AddWEdge<int>(p_graph, 0, 3, 1);
    AddWEdge<int>(p_graph, 0, 1, 2);
    AddWEdge<int>(p_graph, 0, 2, 5);
    AddWEdge<int>(p_graph, 1, 4, 1);
    AddWEdge<int>(p_graph, 2, 4, 3);
    AddWEdge<int>(p_graph, 1, 3, 2);
    AddWEdge<int>(p_graph, 4, 3, 6);

    int mst_weight;
    bool result = p_mst->GetMstWeight(p_graph, &mst_weight);
    ASSERT_TRUE(result);
    EXPECT_EQ(mst_weight, 7);

    WGraph<int> *p_mst_graph = p_creator->CreateWGraph(6, false);
    result = p_mst->GetMst(p_graph, &mst_weight, p_mst_graph);
    ASSERT_TRUE(result);
    EXPECT_EQ(mst_weight, 7);
    EXPECT_EQ(p_mst_graph->GetNumEdges(), 4);
    ASSERT_TRUE(p_mst_graph->HasEdge(0, 3));
    EXPECT_EQ(p_mst_graph->GetEdgeWeight(0, 3), 1);

    ASSERT_TRUE(p_mst_graph->HasEdge(1, 4));
    EXPECT_EQ(p_mst_graph->GetEdgeWeight(1, 4), 1);

    ASSERT_TRUE(p_mst_graph->HasEdge(2, 4));
    EXPECT_EQ(p_mst_graph->GetEdgeWeight(2, 4), 3);

    ASSERT_TRUE(p_mst_graph->HasEdge(1, 0) || p_mst_graph->HasEdge(1, 3));
    if (p_mst_graph->HasEdge(1, 0)) 
        EXPECT_EQ(p_mst_graph->GetEdgeWeight(1, 0), 2);
    else
        EXPECT_EQ(p_mst_graph->GetEdgeWeight(1, 3), 2);

    p_creator->DeleteWGraph(p_graph);
    p_creator->DeleteWGraph(p_mst_graph);
}

TEST(Mst, mst) {
    TestMst<int, int>(TestMst);
}
