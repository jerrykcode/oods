#pragma once
#include "Vertex.h"
#include <vector>
#include <stack>
using namespace std;

typedef enum {
	NOT_RECORD,
	RECORD_PATH,
	RECORD_ALL_PATH,
} RecordType;

class PathRecorder {
public:
	PathRecorder(RecordType record_type);

	RecordType getRecordType();
	virtual bool update(Vertex from, Vertex to) = 0;
	virtual bool add(Vertex from, Vertex to) = 0;
	virtual bool getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths) = 0;
protected:
	RecordType record_type_;
};

class NoPathRecorder : public PathRecorder {
public:
	NoPathRecorder();

	virtual bool update(Vertex from, Vertex to) ;
	virtual bool add(Vertex from, Vertex to);
	virtual bool getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths);
};

class OnePathRecorder : public PathRecorder {
public:
	OnePathRecorder(int n_vertices);
	~OnePathRecorder();

	virtual bool update(Vertex from, Vertex to);
	virtual bool add(Vertex from, Vertex to);
	virtual bool getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths);
private:
	int n_vertices_;
	Vertex * pre_; //pre[v] is the previous vertex of v
};

class AllPathRecorder : public PathRecorder {
public:
	AllPathRecorder(int n_vertices);
	~AllPathRecorder();

	virtual bool update(Vertex from, Vertex to);
	virtual bool add(Vertex from, Vertex to);
	virtual bool getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths);
private:
	bool dfs(Vertex src, Vertex des, vector<vector<Vertex>>& paths, vector<Vertex>& path);

	int n_vertices_;
	vector<Vertex> * pre_; //pre_[v] is all the possible vertices previous to v
};