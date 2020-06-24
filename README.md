# OODS
## Object oriented data structures

## 运行测试

使用[googletest](https://github.com/google/googletest)与cmake测试. 参考[bast](https://github.com/bast)/[gtest-demo](https://github.com/bast/gtest-demo)项目  

### Build
```
git clone git@github.com:jerrykcode/oods.git
cd oods
mkdir build
cd build
cmake ..
cmake --build .
```
### Run
``` $ ctest```

或者

``` $ ./bin/unit_tests```


## Graph图论
![](https://wx2.sinaimg.cn/mw690/006XXwaCgy1gbn012csowj30sr0vfaio.jpg)
### 无权图与有权图

Graph抽象类定义图结构的操作, 子类UnwGraph定义无权图, WGraph\<EdgeWeight\>定义有权图,EdgeWeight为权重类型. UnwGraph和WGraph\<EdgeWeight\>亦为抽象类, 它们均有两个子类分别用邻接矩阵和邻接表实现.
||无权图UnwGraph|有权图 WGraph\<EdgeWeight\>|
|---|---|---|
|邻接矩阵实现|MatrixUnwGraph|MatrixWGraph\<EdgeWeight\>|
|邻接表实现|ListUnwGraph|ListWGraph\<EdgeWeight\>|

### Iterator模式遍历邻接顶点
 Graph及其子类的关系可看成`Iterator模式`, Graph中定义纯虚函数`CreateIterator(Vertex v)`, 该函数返回一个Iterator指针, Iterator也是一个抽象类, 它定义了用于遍历顶点v的所有邻接顶点的纯虚函数. 实现了Graph的子类的CreateIterator(Vertex v)函数则返回实现了Iterator的子类的指针. 
 |Graph的子类|Iteator的子类|
 |---|---|
 |MatrixUnwGraph|MatrixUnwIterator|
 |ListUnwGraph|ListUnwIterator|
 |MatrixWGraph\<EdgeWeight\>|MatrixWIterator\<EdgeWeight\>|
 |ListWGraph\<EdgeWeight\>|ListWIterator\<EdgeWeight\>|
 
 对于Graph指针p_graph, 遍历顶点v的所有邻接顶点:
 ```cpp
Iterator * it = p_graph->CreateIterator(v);
while (it->HasNext()) {
    it->Next();
    Vertex w = it->GetCurrentVertex(); //w is an adjacent vertex of v
}
p_graph->CloseIterator(it);
```
`对于Graph的任何实现子类, 均可使用以上代码遍历一个顶点的邻接点`. 事实上, MatrixWIterator\<EdgeWeight\>和ListWIterator\<EdgeWeight\>没有直接继承Iterator类, 而是继承了WIterator\<EdgeWeight\>类(WIterator\<EdgeWeight\>继承了Iterator). WIterator\<EdgeWeight\>是有权图的迭代器, 可以得到顶点与邻接点之间的边权, 
```cpp
WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)p_graph->CreateIterator(v);
while (it->HasNext()) {
    it->Next();
    Vertex w = it->GetCurrentVertex(); //w is an adjacent vertex of v
    EdgeWeight weight = it->GetCurrentWeight(); //the weight of edge between v and w
}
p_graph->CloseIterator(it);
```
`对于WGraph<EdgeWeight>的实现子类, 可使用以上代码遍历一个顶点的邻接点, 及其与邻接点之间的边权`.

### 有向图与无向图
在Graph的所有子类的构造函数中, 均有一个bool变量用于指定图有向或是无向.

有向图与无向图的区别:
* 向图中插入边(v, w)时, 有向图仅插入一条边, 无向图则插入两条边(v, w)和(w, v)
* 删除图中的一条边(v, w)时, 有向图仅删除一条边, 无向图则删除两条边(v, w)和(w, v)
* 若要得到图的逆图, 有向图需要计算每条边的逆, 而无向图由于与逆图相同, 直接返回deep copy即可

对于有权图, 则有向与无向还有一下区别:
* 改变一条边(v, w)的权重时, 有向图仅改变一条边, 无向图则需要改变(v, w)和(w, v)两条边的权重

对于以上需求, 可以在操作时先判断图有向或是无向. 而这里使用了Graph的内部类Graph::Direction及WGraph\<EdgeWeight\>的内部类WGraph\<EdgeWeight\>::WDirection及它们的子类来`处理有向与无向的不同需求`, 而在Graph及WGraph\<EdgeWeight\>类的层面上`屏蔽了代码差异`.   
以用于插入边(v, w)的AddEdge(Edge \* p_edge)函数为例:

Graph中除了AddEdge函数, 另外再定义一个DoAddEdge(Edge \* p_edge)函数, `这个函数只向图中插入一条边, 而不管图是否有向`  
Direction类中定义纯虚函数```virtual void AddEdge(Graph \* p_graph, Edge \* p_edge) = 0;```  
Direction的子类DirectedType用于处理`有向图的`情况, 它实现的AddEdge函数调用了p_graph的DoAddEdge函数`一次`.  
Direction的另一个子类UnDirectedType用于处理`无向图`的情况, 它实现的AddEdge函数调用了p_graph的DoAddEdge函数`两次`(一次插入一条边, 另一次插入反向边)  
在Graph中组合了一个Direction的指针p_direction_, 而在Graph的构造函数中, 就确定了p_direction_指向的是DirectedType或是UnDirectedType. 在AddEdge函数中, 调用p_direction_的AddEdge: ``` p_direction_->AddEdge(this, p_edge)```, 而p_direction_会根据它是DirectedType还是UnDirectedType来调用相应的AddEdge函数, 也就会相应的调用一次或者两次Graph类的DoAddEdge函数.

对于有权图, 改变边权亦因有向或无向而不同, 所以WGraph\<EdgeWeight\>::WDirection中定义了纯虚函数``` virtual  void  SetEdgeWeight(WGraph<EdgeWeight>  * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) =  0;```用于改变边权. 

### 图论算法

组合Graph实现的图论算法

#### sssp Single Source Shortest Path 单源最短路径

* Djkstra

#### mst Minimum Spanning Tree 最小生成树

* Prim
