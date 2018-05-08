add_executable("main" main.cpp)
#target_link_libraries("main" sfml-graphics sfml-window sfml-system)
target_link_libraries("main" ${SFML_LIBRARIES})

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/*
                ${CMAKE_CURRENT_BINARY_DIR} )
