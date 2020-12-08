add_library(sssp "")

target_sources(
    sssp
    PRIVATE
        path_recorder.cc
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/path_recorder.h
    )

target_include_directories(
    sssp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
