add_executable("test_isort" test-isort.cpp)
target_link_libraries("test_isort"  googletest pthread)

add_test(
  NAME test_isort
  COMMAND test_isort
)
