add_executable("test_op" test-op.cpp)
target_link_libraries("test_op" googletest pthread)


add_test(
  NAME test_op
  COMMAND test_op
)
