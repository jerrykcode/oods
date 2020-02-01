#pragma once
#include "../../graph/vertex.h"
#include <cstring>
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace oods 
{
    namespace oograph
    {
        class Path {
        public:
            void AddVertex(Vertex v) {
                path_.push_back(v);
            }
            
            vector<Vertex>& GetPathRef() {
                return path_;
            }

            vector<Vertex> GetPathCopy() {
                vector<Vertex> path;
                path.resize(path_.size());
                for (int i = 0; i < path_.size(); i++)
                    path[i] = path_[i];
                return path;
            }

            /*string GetPathString(string connection) {
                string s = "";
                for (auto it = path_.begin(); it != path_.end(); it++) {
                    s += *it;
                    if (it != path_.end()) s += connection;
                }
                return s;
            }*/
        private:
            vector<Vertex> path_;
        };
    }
}
