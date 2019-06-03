#pragma once
#include "Vertex.h"
#include <queue>
using namespace std;

class VertexQueue {
public:
	virtual void push(Vertex v) = 0;
	virtual Vertex top() = 0;
	virtual void pop() = 0;
	virtual bool empty() = 0;
};

class Queue : public VertexQueue {
public:
	virtual void push(Vertex v) {
		queue_.push(v);
	}

	virtual Vertex top() {
		return queue_.front();
	}

	virtual void pop() {
		queue_.pop();
	}

	virtual bool empty() {
		return queue_.empty();
	}

private:
	queue<Vertex> queue_;
};

class PriorityQueue : public VertexQueue {
public:
	virtual void push(Vertex v) {
		pqueue_.push(v);
	}

	virtual Vertex top() {
		return pqueue_.top();
	}

	virtual void pop() {
		pqueue_.pop();
	}

	virtual bool empty() {
		return pqueue_.empty();
	}

private:
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pqueue_;
};