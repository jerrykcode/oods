add_executable(
    unit_tests
    testcase.cc
    graph/graph/test_unw_graph.cc
    graph/graph/test_w_graph.cc
    graph/algorithms/sssp/test_sssp.cc
    graph/algorithms/sssp/test_sssp_1.cc
    graph/algorithms/sssp/test_sssp_2.cc
    )

include_directories(
        ../src/graph/graph/
        ../src/graph/graph/impl
        ../src/graph/algorithms/sssp
        ../src/graph/algorithms/sssp/impl
        include
    )

target_link_libraries(
    unit_tests
    gtest_main
    sssp
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
