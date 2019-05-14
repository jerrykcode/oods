#include "pathRecorder.h"

//PathRecorder
PathRecorder::PathRecorder(RecordType record_type) : record_type_(record_type) {

}

RecordType PathRecorder::getRecordType() {
	return record_type_;
}

//NoPathRecorder
NoPathRecorder::NoPathRecorder() : PathRecorder(NOT_RECORD) {

}

bool NoPathRecorder::update(Vertex from, Vertex to) {
	return false;
}

bool NoPathRecorder::add(Vertex from, Vertex to) {
	return false;
}

bool NoPathRecorder::getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths) {
	return false;
}

//OnePathRecorder
OnePathRecorder::OnePathRecorder(int n_vertices) : PathRecorder(RECORD_PATH) , n_vertices_(n_vertices) {
	pre_ = new Vertex[n_vertices_];
	fill(pre_, pre_ + n_vertices_, n_vertices_); //pre_[i] initialized to be n_vertices_, while normal vertices indexed form 0 to n_vertices_ - 1
}

OnePathRecorder::~OnePathRecorder() {
	free(pre_);
}

bool OnePathRecorder::update(Vertex from, Vertex to) {
	if (from >= n_vertices_) return false;
	if (to >= n_vertices_) return false;
	pre_[to] = from;
	return true;
}

bool OnePathRecorder::add(Vertex from, Vertex to) {
	return false;
}

bool OnePathRecorder::getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths) {
	if (src >= n_vertices_) return false;
	vector<Vertex> path;
	stack<Vertex> s;
	for (; des != src; des = pre_[des]) {
		s.push(des);
		if (des >= n_vertices_) {
			stack<Vertex>().swap(s);
			return false;
		}
	}
	path.push_back(src);
	while (!s.empty()) {
		path.push_back(s.top());
		s.pop();
	}
	stack<Vertex>().swap(s);
	paths.push_back(path);
	return true;
}

//AllPathRecorder
AllPathRecorder::AllPathRecorder(int n_vertices) : PathRecorder(RECORD_ALL_PATH), n_vertices_(n_vertices) {
	pre_ = new vector<Vertex>[n_vertices];
}

AllPathRecorder::~AllPathRecorder() {
	for (size_t i = 0; i < n_vertices_; i++)
		vector<Vertex>().swap(pre_[i]);
}

bool AllPathRecorder::update(Vertex from, Vertex to) {
	if (from >= n_vertices_) return false;
	if (to >= n_vertices_) return false;
	pre_[to].clear();
	pre_[to].push_back(from);
	return true;
}

bool AllPathRecorder::add(Vertex from, Vertex to) {
	if (from >= n_vertices_) return false;
	if (to >= n_vertices_) return false;
	pre_[to].push_back(from);
	return true;
}

bool AllPathRecorder::getPath(Vertex src, Vertex des, vector<vector<Vertex>>& paths) {
	vector<Vertex> path;
	bool result = dfs(src, des, paths, path);
	vector<Vertex>().swap(path);
	return result;
}

bool AllPathRecorder::dfs(Vertex src, Vertex des, vector<vector<Vertex>>& paths, vector<Vertex>& path) {
	if (des >= n_vertices_) return false;
	path.push_back(des);
	if (src == des) {
		vector<Vertex> tmp_path;
		tmp_path.resize(path.size());
		for (size_t i = 0; i < path.size(); i++)
			tmp_path[i] = path[path.size() - i - 1];
		paths.push_back(tmp_path);
		return true;
	}
	for (Vertex v : pre_[des]) {
		if (!dfs(src, v, paths, path)) return false;
		path.pop_back();
	}
	return true;
}