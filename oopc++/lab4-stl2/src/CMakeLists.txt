add_library("stl_lib" zadatak.cpp)
add_executable("stl" main.cpp)
target_link_libraries("stl" "stl_lib")

add_custom_command(
        TARGET stl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/src/*.txt
                ${CMAKE_CURRENT_BINARY_DIR})
