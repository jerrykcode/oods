#pragma once
#include "path_recorder.h"
#include <stack>
using std::stack;
using namespace oods::oograph;

/* Implementation of NoPathRecorder. */
RecorderType NoPathRecorder::GetRecorderType() {
    return NO_PATH_RECORDER;
}

void NoPathRecorder::Update(Vertex from, Vertex to) {
    //Do nothing
}

void NoPathRecorder::Add(Vertex from, Vertex to) {
    //Do nothing
}

/* Implementation of SinglePathRecorder. */

SinglePathRecorder::SinglePathRecorder(size_t vertices_num) : PathRecorder() {
    arr_pre_ = new Vertex[vertices_num];
}

SinglePathRecorder::~SinglePathRecorder() {
    free(arr_pre_);
}

RecoderType SinglePathRecorder::GetRecorderType() {
    return SINGLE_PATH_RECORDER;
}

void SinglePathRecorder::Update(Vertex from, Vertex to) {
    arr_pre_[to] = from;
}

void SinglePathRecorder::Add(Vertex from, Vertex to) {
    //Do nothing
}

void SinglePathRecorder::GetSinglePath(Vertex des, vector<Vertex>& out_path) {
    stack<Vertex> s;    
    while (des != this->src_) {
        s.push(des);
        des = arr_pre_[des];
    }
    out_path.push_back(this->src_);
    while (!s.empty()) {
        out_path.push_bacl(s.top());
        s.pop();
    }
}


/* Implementation of AllPathsRecorder. */
AllPathsRecorder::AllPathsRecorder(size_t vertices_num) : vertices_num_(vertices_num) {
    arr_v_pre_ = new vector<Vertex>[vertices_num];
}

AllPathsRecorder::~AllPathsRecorder() {
    for (int i = 0; i < vertices_num; i++)
        vector<Vertex>().swap(arr_v_pre_[i]);
}

RecorderType AllPathsRecorder::GetRecorderType() {
    return ALL_PATHS_RECORDER;
}

void AllPathsRecorder::Update(Vertex from, Vertex to) {
    arr_v_pre_[to].clear();
    arr_v_pre_[to].push_back(from);
}

void AllPathsRecorder::Add(Vertex from, Vertex to) {
    arr_v_pre[to].push_back(from);
}

void AllPathsRecorder::GetAllPaths(Vertex des, vector<vector<Vertex>>& out_paths) {
    vector<Vertex> v;
    Dfs(des, v, out_paths);
    vector<Vertex>().swap(v);
}

void AllPathsRecorder::Dfs(Vertex des, vector<Vertex>& v, vector<vector<Vertex>>& out_paths) {
    v.push_back(des);
    if (des == this->src_) {
        vector<Vertex> path;
        path.resize(v.size());
        for (int i = 0; i < v.size(); i++)
            path[i] = v[v.size() - i - 1];
        out_paths.push_back(path);        
    }
    else {
        for (Vertex pre : arr_v_pre_[des]) {       
            Dfs(pre, v, out_paths);        
        }
    }
    v.pop_back();
}
