#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

#define NO_VALUE -1

typedef int Vertex;

//Define edge
class Edge {
public:
	Edge() {}
	Edge(Vertex v, Vertex w) : v(v), w(w) {}
	~Edge() {}

	virtual void getVertexes(Vertex *pv, Vertex *pw) = 0;
	virtual bool isWeighted() = 0;

protected:
	Vertex v, w;
};

class UNWEdge : public Edge { //UnWeighted edge
public:
	UNWEdge(Vertex v, Vertex w) : Edge(v, w) {}

	virtual void getVertexes(Vertex *pv, Vertex *pw) {
		*pv = this->v;
		*pw = this->w;
	}

	virtual bool isWeighted() {
		return false;
	}
};

template<typename T>
class WEdge : public Edge { //Weighted edge
public:
	WEdge(Vertex v, Vertex w, T weight) : Edge(v, w), weight_(weight) {}

	virtual void getVertexes(Vertex *pv, Vertex *pw) {
		*pv = this->v;
		*pw = this->w;
	}

	virtual bool isWeighted() {
		return true;
	}

	T getWeight() {
		return weight_;
	}
private:
	T weight_;
};

//Define adjacent note
class AdjNode {
public:
	AdjNode() {}
	AdjNode(Vertex adjVertex) : adjVertex_(adjVertex) {}
	~AdjNode() {}

	virtual Vertex getAdjVertex() = 0;
	virtual bool isWeighted() = 0;

protected:
	Vertex adjVertex_;
};

class UNWAdjNode : public AdjNode { //UnWeighted adjacent note
public:
	UNWAdjNode() {}
	UNWAdjNode(Vertex adjVertex) : AdjNode(adjVertex) {}

	virtual Vertex getAdjVertex() {
		return this->adjVertex_;
	}

	virtual bool isWeighted() {
		return false;
	}
};

template<typename T>
class WAdjNode : public AdjNode { //Weighted adjacent node
public:
	WAdjNode() {}
	WAdjNode(Vertex adjVertex, T adjWeight) : AdjNode(adjVertex), adjWeight_(adjWeight) {}

	virtual Vertex getAdjVertex() {
		return this->adjVertex_;
	}

	virtual bool isWeighted() {
		return true;
	}

	T getAdjWeight() {
		return adjWeight_;
	}

	void increaseAdjWeight(T weight) {
		adjWeight_ += weight;
	}

private:
	T adjWeight_;
};


//Define Graph
class Graph {
public:
	Graph() {}
	Graph(int nVertexes, int nEdges, bool isDirected) : nVertexes_(nVertexes), nEdges_(nEdges), isDirected_(isDirected) {}
	~Graph() {}

	int getVertexesNum() { return nVertexes_; }
	int getEdgesNum() { return nEdges_; }

	bool isDirected() { return isDirected_; }

	virtual void insertEdge(Edge *pEdge) = 0;
	virtual AdjNode * adj_iter_begin(Vertex v) = 0;
	virtual AdjNode * adj_iter_next() = 0;
	virtual void adj_iter_clear() = 0;
	virtual void clear() = 0;
	virtual bool isWeighted() = 0;

	virtual Graph *cloneGraph() = 0;
	virtual Graph *inverseGraph() = 0;

protected:
	int nVertexes_;
	int nEdges_;
	bool isDirected_;

	typedef struct IterArgs {
		Vertex iter_v_;
		int iter_count_;
		IterArgs(Vertex iter_v, int iter_count) : iter_v_(iter_v), iter_count_(iter_count) {}
	} *PIterArgs;

	stack<PIterArgs> pIterArgs_stack_;
};

class UNWGraph : public Graph { //UnWeighted Graph
public:
	UNWGraph(int nVertexes, int nEdges, bool isDirected) : Graph(nVertexes, nEdges, isDirected) {}

	virtual void insertEdge(Edge *pEdge) = 0;
	virtual AdjNode * adj_iter_begin(Vertex v) = 0;
	virtual AdjNode * adj_iter_next() = 0;
	virtual void adj_iter_clear() = 0;
	virtual void clear() = 0;
	virtual bool isWeighted() = 0;

	virtual Graph *cloneGraph() = 0;
	virtual Graph *inverseGraph() = 0;
};

template<typename T>
class WGraph : public Graph { //Weighted Graph
public:
	WGraph(int nVertexes, int nEdges, bool isDirected) : Graph(nVertexes, nEdges, isDirected) {}

	virtual void insertEdge(Edge *pEdge) = 0;
	virtual AdjNode * adj_iter_begin(Vertex v) = 0;
	virtual AdjNode * adj_iter_next() = 0;
	virtual void adj_iter_clear() = 0;
	virtual void clear() = 0;
	virtual bool isWeighted() = 0;

	virtual T getEdgeWeight(Vertex v, Vertex w) = 0;
	virtual void increaseEdgeWeight(Vertex v, Vertex w, T weight) = 0;

	virtual Graph *cloneGraph() = 0;
	virtual Graph *inverseGraph() = 0;
};

//define Vertex Queue
typedef struct QNode {
	Vertex v;
	struct QNode *next;
	QNode(Vertex v) : v(v), next(NULL) {}
} *QList;

class VQueue {
public:
	VQueue();
	~VQueue();

	void push(Vertex v);
	Vertex pop();
	bool empty();

private:
	QList head, tail;
};

inline VQueue::VQueue() : head(NULL), tail(NULL) {

}

inline VQueue::~VQueue() {
	while (!empty()) pop();
}

inline void VQueue::push(Vertex v) {
	QList qlist = new QNode(v);
	if (head == NULL) {
		head = tail = qlist;
	}
	else {
		tail->next = qlist;
		tail = qlist;
	}
}

inline Vertex VQueue::pop() {
	if (empty()) return NO_VALUE;
	QList qlist = head;
	head = head->next;
	Vertex v = qlist->v;
	delete qlist;
	return v;
}

inline bool VQueue::empty() {
	return head == NULL;
}