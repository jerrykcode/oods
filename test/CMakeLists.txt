add_executable(
    unit_tests
    testcase.cc
    graph/graph/test_unw_graph.cc
    graph/graph/test_w_graph.cc
    )

include_directories(
        ../src/graph/graph/
        ../src/graph/graph/impl
    )

target_link_libraries(
    unit_tests
    gtest_main
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
