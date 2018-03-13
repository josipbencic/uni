add_executable("test_zad" test-zad.cpp)
target_link_libraries("test_zad" "stl_lib" googletest pthread)


add_test(
  NAME test_zad
  COMMAND test_zad
)
