#include "path_recorder.h"
#include <stack>
#include <algorithm>
using std::stack;
using namespace oods::oograph;

/* Implementation of NoPathRecorder. */
NoPathRecorder::NoPathRecorder() { }
NoPathRecorder::~NoPathRecorder() { }

RecorderType NoPathRecorder::GetRecorderType() {
    return NO_PATH_RECORDER;
}

void NoPathRecorder::Update(Vertex from, Vertex to) {
    //Do nothing
}

void NoPathRecorder::Add(Vertex from, Vertex to) {
    //Do nothing
}

void NoPathRecorder::Clear() {
    //Do nothing
}

/* Implementation of SinglePathRecorder. */

SinglePathRecorder::SinglePathRecorder(size_t vertices_num) : PathRecorder(), vertices_num_(vertices_num) {
    arr_pre_ = new Vertex[vertices_num];
    std::fill(arr_pre_, arr_pre_ + vertices_num, NOT_A_VERTEX);
}

SinglePathRecorder::~SinglePathRecorder() {
    free(arr_pre_);
}

RecorderType SinglePathRecorder::GetRecorderType() {
    return SINGLE_PATH_RECORDER;
}

void SinglePathRecorder::Update(Vertex from, Vertex to) {
    arr_pre_[to] = from;
}

void SinglePathRecorder::Add(Vertex from, Vertex to) {
    //Do nothing
}

void SinglePathRecorder::Clear() {
    std::fill(arr_pre_, arr_pre_ + vertices_num_, NOT_A_VERTEX);
}

void SinglePathRecorder::GetSinglePath(Vertex src, Vertex des, Path * p_out_path) {
    stack<Vertex> s;
    while (des != src) {
        s.push(des);
        des = arr_pre_[des];
    }
    p_out_path->AddVertex(src);
    while (!s.empty()) {
        p_out_path->AddVertex(s.top());
        s.pop();
    }
}


/* Implementation of AllPathsRecorder. */
AllPathsRecorder::AllPathsRecorder(size_t vertices_num) : vertices_num_(vertices_num) {
    arr_v_pre_ = new vector<Vertex>[vertices_num];
}

AllPathsRecorder::~AllPathsRecorder() {
    for (int i = 0; i < vertices_num_; i++)
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
    arr_v_pre_[to].push_back(from);
}

void AllPathsRecorder::Clear() {
    for (int i = 0; i < vertices_num_; i++)
        arr_v_pre_[i].clear();
}

void AllPathsRecorder::GetAllPaths(Vertex src, Vertex des, vector<Path *>& out_paths) {
    vector<Vertex> v;
    Dfs(src, des, v, out_paths);
    vector<Vertex>().swap(v);
}

void AllPathsRecorder::Dfs(Vertex src, Vertex des, vector<Vertex>& v, vector<Path *>& out_paths) {
    v.push_back(des);
    if (des == src) {
        Path * p_path = new Path();        
        for (auto it = v.end() - 1; it >= v.begin(); it--) //inverse order
            p_path->AddVertex(*it);
        out_paths.push_back(p_path);
    }
    else {
        for (Vertex pre : arr_v_pre_[des]) {       
            Dfs(src, pre, v, out_paths);        
        }
    }
    v.pop_back();
}
