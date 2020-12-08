add_library(scc "")

target_sources(
    scc
    PRIVATE
        impl/tarjan.cc
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/impl/tarjan.h
    )

target_include_directories(
    scc
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/impl
    )
