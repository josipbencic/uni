add_executable("main" main.cpp
                      game.cpp
                      world.cpp
                      snake.cpp
                      playing_state.cpp
                      aux_states.cpp
                      game.h
                      snake.h
                      world.h
                      game_state.h
                      playing_state.h
                      aux_states.h)

target_link_libraries("main" ${SFML_LIBRARIES})
target_compile_features("main" PRIVATE cxx_range_for)

# Kopiraj fontove u direktorij programa.
add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/doc/*.ttf
                ${CMAKE_CURRENT_BINARY_DIR} )
