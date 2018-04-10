add_executable("test_zad" test-zad.cpp)
target_link_libraries("test_zad" googletest pthread)


add_executable("test_remove" test-remove.cpp)
target_link_libraries("test_remove" googletest pthread)

#add_custom_command(
#        TARGET test_zad POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_SOURCE_DIR}/test/*.txt
#                ${CMAKE_CURRENT_BINARY_DIR})
add_test(
  NAME test_zad
  COMMAND test_zad
)

add_test(
  NAME test_remove
  COMMAND test_remove
)
