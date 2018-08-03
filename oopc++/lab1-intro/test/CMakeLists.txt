add_executable("test_zad" test-zad.cpp)
#add_dependencies("test-zad" googletest)

target_link_libraries("test_zad" "intro_lib" googletest pthread)
#target_link_libraries("test_zad" "stl_lib" ${GTEST_BOTH_LIBRARIES} pthread)

add_test(
  NAME test_zad
  COMMAND test_zad
  )
