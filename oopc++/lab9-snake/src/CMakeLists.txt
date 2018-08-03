add_executable("snake" main.cpp game.cpp world.cpp snake.cpp game.h snake.h world.h)
#target_link_libraries("main-1" sfml-graphics sfml-window sfml-system)
target_link_libraries("snake" ${SFML_LIBRARIES})
target_compile_features("snake" PRIVATE cxx_range_for)

