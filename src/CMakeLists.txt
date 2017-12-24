add_library("stl_lib" zadatak.cpp)
add_executable("stl" main.cpp)
target_link_libraries("stl" "stl_lib")
