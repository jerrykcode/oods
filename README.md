# OOGraph

## Graph

![graph_uml](http://wx1.sinaimg.cn/mw690/006XXwaCgy1g2ztcv8hq5j30ns0l7wj4.jpg)

Graph抽象类定义图结构的操作，子类UNWGraph抽象类表示无权图，子类WGraph`<T>`表示有权图，T为边的权重。UNWGraph分别用邻接表和邻接矩阵实现为ListUNWGraph类和MatrixUNWGraph类，WGraph`<T>`分别用邻接表和邻接矩阵实现为ListWGraph`<T>`类和MatrixWGraph`<T>`类。

Graph抽象类中定义纯虚函数:

```virtual Iterator * getAdjIterator(Vertex v) = 0;```

用于返回顶点v的邻接点迭代器，同时Iterator类亦为抽象类，定义纯虚函数：

```virtual AdjNode * next() = 0;```

AdjNode定义邻接点，其子类UNWAdjNode表示无权图中一个顶点的邻接点；WAdjNode<T>表示有权图中一个顶点的邻接点。


Iterator类的4个子类分别对应Graph类的4个实现子类。

使用Iterator模式可遍历一个顶点的邻接点:

```cpp
//遍历图Graph * p_graph中顶点v的邻接点
Iterator * it = p_graph->getAdjIterator(v);
for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
	Vertex adj_v = p_adj_node->getAdjVertex(); //邻接点
}
```

对于Graph类的所有子类均可使用以上代码遍历邻接点，p_graph调用getAdjIterator(v)会根据p_graph指向的内存是哪个子类的实例返回相应的Iteartor类的子类，it调用next()又会根据it指向的具体子类执行其实现的next函数。

对于有权图WGraph`<T>`*，可以得到v与邻接点之间边的权重：

```cpp
Iterator * it = p_graph->getAdjIterator(v);
for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
	Vertex adj_v = p_adj_node->getAdjVertex(); //邻接点
	T adj_weight = ((WAdjNode<T> *)p_adj_node)->getAdjWeight(); //邻接边权重
}
```
p_graph为WGraph`<T>`的子类的指针，其调用getAdjIterator(v)返回的Iterator指针指向的内存一定是ListWIterator`<T>`或MatrixWIterator`<T>`的实例，那么it调用next()返回的AdjNode指针指向的内存一定是WAdjNode`<T>`的实例，所以将p_adj_node cast成WAdjNode`<T>`指针即可调用getAdjWeight()函数得到边权。

## Algorithm

组合Graph实现的图论算法

### SSSP (Single source shortest path 单源最短路径)

* Dijkstra

* A*

### MST (Minimum spanning tree 最小生成树)

* Prim

### SCC (Strongly connected component 强连通分量)

* Tarjan

### MF (Maximum flow 最大流)

* Dinic

### TopSort (Topological sort 拓扑排序)

* DAG(判断是否有环， 求拓扑序列)

* Critical path(计算AOE图的关键路径)