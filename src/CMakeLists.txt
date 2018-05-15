add_executable("main" main.cpp game-v1.h game-v1.cpp)
add_executable("zadatak1" main2.cpp game-v2.h game-v2.cpp)
add_executable("zadatak2" main3.cpp game-v3.h game-v3.cpp)

#target_link_libraries("main" sfml-graphics sfml-window sfml-system)
target_link_libraries("main" ${SFML_LIBRARIES})
target_compile_features(main PRIVATE cxx_range_for)

target_link_libraries("zadatak1" ${SFML_LIBRARIES})
target_compile_features(zadatak1 PRIVATE cxx_range_for)

target_link_libraries("zadatak2" ${SFML_LIBRARIES})
target_compile_features(zadatak2 PRIVATE cxx_range_for)


add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/*
                ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command(
        TARGET zadatak1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/*
                ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command(
        TARGET zadatak2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/*
                ${CMAKE_CURRENT_BINARY_DIR} )
