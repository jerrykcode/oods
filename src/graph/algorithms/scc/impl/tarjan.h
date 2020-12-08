#pragma once
#include "../scc.h"
#include <stack>
using std::stack;

namespace oods {
    namespace oograph {
        class Tarjan : public Scc {
        public:
            /* @function StrongConnectedComponents
             * Mark all the scc(Strong Connected Components) in a graph
             * @param p_graph Pointer to the graph
             * @param arr_out_color An array, arr_out_color[v] is the scc 'v' belongs to. This is an out parameter
             * @param p_out_scc_num A pointer points to the number of the strong connected components in the graph. This is an out parameter
             * @return void
             * */
            virtual void StrongConnectedComponents(Graph *p_graph, int *arr_out_color, size_t *p_out_scc_num);
         

        private:
            int *arr_dfn_;
            int *arr_low_;
            int v_index_;
            stack<Vertex> stack_;
            bool *arr_instack_;
            Graph *p_graph_;
            int *arr_color_;
            int color_count_;

            void Dfs(Vertex v);
        };
    }
}
