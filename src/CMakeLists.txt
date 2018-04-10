add_executable("bst" main.cpp bin_stablo.h bin_stablo_impl.h)

#add_custom_command(
#        TARGET stl POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_SOURCE_DIR}/src/*.txt
#                ${CMAKE_CURRENT_BINARY_DIR})
