add_executable("test_zad" test-zad.cpp)
target_link_libraries("test_zad" "stl_lib" ${GTEST_BOTH_LIBRARIES} pthread)
