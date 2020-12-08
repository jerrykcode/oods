#include "gtest/gtest.h"
#include <stdarg.h>
#include "test.h"
#include "addedge.h"

bool AllEqual(int num, ...) {
    //Returns ture if all the numbers are equal to each other
    va_list ap;
    va_start(ap, num);

    int first = va_arg(ap, int);
    for (int i = 1; i < num; i++)
        if (va_arg(ap, int) != first)
            return false;
    va_end(ap);

    return true;
}

void _TestScc(Scc *p_scc, UnwGraphCreator *p_creator) {
    UnwGraph *p_graph = p_creator->CreateUnwGraph(10, true);
    AddUnwEdge(p_graph, 0, 1);
    AddUnwEdge(p_graph, 1, 3);
    AddUnwEdge(p_graph, 3, 0);
    AddUnwEdge(p_graph, 1, 2);
    AddUnwEdge(p_graph, 2, 4);
    AddUnwEdge(p_graph, 4, 5);
    AddUnwEdge(p_graph, 5, 6);
    AddUnwEdge(p_graph, 6, 2);
    AddUnwEdge(p_graph, 2, 7);
    AddUnwEdge(p_graph, 1, 8);
    AddUnwEdge(p_graph, 8, 9);

    size_t scc_num;
    int *arr_color = new int[10];
    p_scc->StrongConnectedComponents(p_graph, arr_color, &scc_num);
    EXPECT_EQ(scc_num, 5);
    //0, 1, 3 are in a same scc
    ASSERT_TRUE(AllEqual(3, arr_color[0], arr_color[1], arr_color[3]));
    //2, 4, 5, 6 are in a same scc
    ASSERT_TRUE(AllEqual(4, arr_color[2], arr_color[4], arr_color[5], arr_color[6]));
    delete arr_color;
}

TEST(Scc, scc) {
    TestScc(_TestScc);
}
