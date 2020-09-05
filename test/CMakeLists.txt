add_executable(
    unit_tests
    testcase.cc
    graph/graph/test_unw_graph.cc
    graph/graph/test_w_graph.cc
    graph/algorithms/sssp/test_sssp.cc
    graph/algorithms/sssp/test_sssp_1.cc
    graph/algorithms/sssp/test_sssp_2.cc
    graph/algorithms/mst/test_mst.cc
    graph/algorithms/scc/test_scc.cc
    )

include_directories(
        ../src/graph/graph/
        ../src/graph/graph/impl
        ../src/graph/algorithms/sssp
        ../src/graph/algorithms/sssp/impl
        ../src/graph/algorithms/mst
        ../src/graph/algorithms/mst/impl
        ../src/graph/algorithms/scc/
        ../src/graph/algorithms/scc/impl
        include
    )

target_link_libraries(
    unit_tests
    gtest_main
    sssp
    scc
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
