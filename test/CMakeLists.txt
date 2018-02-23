add_executable("test_isort" test-isort.cpp)
#add_dependencies("test-zad" googletest)



target_link_libraries("test_isort"  googletest pthread)
