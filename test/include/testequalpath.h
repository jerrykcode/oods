#pragma once

#include "gtest/gtest.h"
#include <vector>
#include "path.h"
using namespace std;
using namespace oods::oograph;

static void TestEqualPath(Path * p_path, std::initializer_list<Vertex> list) {
    vector<Vertex>& p_ref = p_path->GetPathRef();
    EXPECT_EQ(p_ref.size(), list.size());
    auto vi = p_ref.begin();
    auto li = list.begin();
    while (vi != p_ref.end()) {
        EXPECT_EQ(*vi, *li);
        vi++;
        li++;
    }
}

static bool ComparePath(Path * a, Path * b) {
    vector<Vertex>& a_ref = a->GetPathRef();
    vector<Vertex>& b_ref = b->GetPathRef();
    for (int i = 0; i < std::min(a_ref.size(), b_ref.size()); i++) {
        if (a_ref[i] < b_ref[i]) return true;
        if (a_ref[i] > b_ref[i]) return false;
        //if a_ref[i] == b_ref[i] then continue
    }
    return a_ref.size() < b_ref.size();
}

static void DeletePaths(vector<Path *>& paths) {
    for (auto p_path : paths) {
        delete p_path;
    }
    paths.clear();
}
