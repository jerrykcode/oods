#pragma once
#include "vertex.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {

        typedef enum {
            NO_PATH_RECORDER,
            SINGLE_PATH_RECORDER,
            ALL_PATHS_RECORDER
        } RecoderType;

        class PathRecorder {
        public:
           void setSrc(Vertex src) {
                src_ = src;
           }
           virtual RecorderType GetRecorderType() = 0; 
           virtual void Update(Vertex from, Vertex to) = 0;
           virtual void Add(Vertex from, Vertex to) = 0;
           virtual ~PathRecorder() {} //Virtual destructor
        protected: 
            Vertex src_;
        };

        class NoPathRecorder : public PathRecorder {
        public:

        };

        class SinglePathRecoder : public PathRecorder {
        public:
            SinglePathRecorder(size_t vertices_num);
            ~SinglePathRecorder();
            void GetSinglePath(Vertex des, vector<Vertex>& out_path);
        private:
            Vertex * arr_pre_;
        };

        class AllPathsRecorder : public PathRecorder {
        public:
            AllPathsRecorder(size_t vertices_num);
            ~AllPathsRecorder();
            void GetAllPaths(Vertex des, vector<vector<Vertex>>& out_paths);
        private:
            vector<Vertex> * arr_v_pre_;
            size_t vertices_num_;

            void Dfs(Vertex des, vector<Vertex>& v, vector<vector<Vertex>>& out_paths);
        };
    }

}
