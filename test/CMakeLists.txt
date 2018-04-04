add_executable("test_zad" test-zad.cpp test-lista.h)
target_link_libraries("test_zad" googletest pthread)

add_test(
  NAME test_zad
  COMMAND test_zad
)
