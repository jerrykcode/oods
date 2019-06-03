#pragma once
#include "Vertex.h"
#include <vector>
using namespace std;

class VertexCounter {
public:
	virtual void count(Vertex v) = 0;
	virtual size_t size() = 0;
};

class Counter : public VertexCounter {
public:
	Counter() : count_(0) {}

	virtual void count(Vertex v) {
		count_++;
	}

	virtual size_t size() {
		return count_;
	}
private:
	size_t count_;
};

class VertexSequence : public VertexCounter {
public:

	VertexSequence(vector<Vertex>& sequence) : sequence_(sequence) {}

	virtual void count(Vertex v) {
		sequence_.push_back(v);
	}

	virtual size_t size() {
		return sequence_.size();
	}
private:
	vector<Vertex>& sequence_;
};