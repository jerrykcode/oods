#pragma once
#include "path.h"
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
        } RecorderType;

        class PathRecorder {
        public:
            PathRecorder() {}
            virtual ~PathRecorder() {} //Virtual destructor
            virtual RecorderType GetRecorderType() = 0; 
            virtual void Update(Vertex from, Vertex to) = 0;
            virtual void Add(Vertex from, Vertex to) = 0;
            virtual void Clear() = 0;
        };

        class NoPathRecorder : public PathRecorder {
        public:
            NoPathRecorder();
            ~NoPathRecorder();
            virtual RecorderType GetRecorderType(); 
            virtual void Update(Vertex from, Vertex to);
            virtual void Add(Vertex from, Vertex to);
            virtual void Clear();
        };

        class SinglePathRecorder : public PathRecorder {
        public:
            SinglePathRecorder(size_t vertices_num);
            ~SinglePathRecorder();
            virtual RecorderType GetRecorderType(); 
            virtual void Update(Vertex from, Vertex to);
            virtual void Add(Vertex from, Vertex to);
            virtual void Clear();

            void GetSinglePath(Vertex src, Vertex des, Path * p_out_path);
        private:
            Vertex * arr_pre_;
            size_t vertices_num_;
        };

        class AllPathsRecorder : public PathRecorder {
        public:
            AllPathsRecorder(size_t vertices_num);
            ~AllPathsRecorder();  
            virtual RecorderType GetRecorderType(); 
            virtual void Update(Vertex from, Vertex to);
            virtual void Add(Vertex from, Vertex to);
            virtual void Clear();

            void GetAllPaths(Vertex src, Vertex des, vector<Path *>& out_paths);
        private:
            vector<Vertex> * arr_v_pre_;
            size_t vertices_num_;

            void Dfs(Vertex src, Vertex des, vector<Vertex>& v, vector<Path *>& out_paths);
        };
    }

}
