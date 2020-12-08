#include "tarjan.h"
#include <algorithm>

using namespace oods::oograph;
using std::fill;

void Tarjan::StrongConnectedComponents(Graph *p_graph, int *arr_out_color, size_t *p_out_scc_num) {
    //Initialize
    p_graph_ = p_graph;
    arr_color_ = arr_out_color;
    
    size_t num_vertices = p_graph_->GetNumVertices();
    arr_dfn_ = new int[num_vertices];
    fill(arr_dfn_, arr_dfn_ + num_vertices, 0);
    arr_low_ = new int[num_vertices];
    fill(arr_low_, arr_low_ + num_vertices, 0);
    v_index_ = 1;
    arr_instack_ = new bool[num_vertices];
    fill(arr_instack_, arr_instack_ + num_vertices, false);
    color_count_ = 0;

    //DFS
    for (Vertex v = 0; v < num_vertices; v++) {
        if (!arr_dfn_[v]) 
            Dfs(v);
    }

    *p_out_scc_num = color_count_;

    //free memory
    delete arr_dfn_;
    delete arr_low_;
    delete arr_instack_;
    stack<Vertex>().swap(stack_);
}

void Tarjan::Dfs(Vertex v) {
    arr_dfn_[v] = arr_low_[v] = v_index_++;
    stack_.push(v);
    arr_instack_[v] = true;
    Iterator *it = p_graph_->CreateIterator(v);
    Vertex w;
    while (it->HasNext()) {
        it->Next();
        w = it->GetCurrentVertex();
        if (!arr_dfn_[w]) {
            Dfs(w);
            arr_low_[v] = std::min(arr_low_[v], arr_low_[w]);
        }
        else if (arr_instack_[w])
            arr_low_[v] = std::min(arr_low_[v], arr_dfn_[w]);
    }
    if (arr_dfn_[v] == arr_low_[v]) {
        while (true) {
            w = stack_.top(); stack_.pop();
            arr_instack_[w] = false;
            arr_color_[w] = color_count_;
            if (w == v) break;
        }
        color_count_++;
    }
}
