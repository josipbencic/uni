add_library("intro_lib" zadatak.cpp)
add_executable("intro" main.cpp)
target_link_libraries("intro" "intro_lib")

add_custom_command(
        TARGET intro POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/src/*.txt
                ${CMAKE_CURRENT_BINARY_DIR})
