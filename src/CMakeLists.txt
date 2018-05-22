add_executable("main" main.cpp sceneGraph.cpp sceneGraph.h game.cpp game.h )
#target_link_libraries("main" sfml-graphics sfml-window sfml-system)
target_link_libraries("main" ${SFML_LIBRARIES})
target_compile_features(main  PUBLIC cxx_constexpr)

# Kreira direktorij za vrijeme konfiguracije
if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/Textures/")
  file (MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Textures/")
  message ("Generating Textures directory")
endif ()


add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/Desert.png ${CMAKE_CURRENT_BINARY_DIR}/Textures 
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/Raptor.png ${CMAKE_CURRENT_BINARY_DIR}/Textures 
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/Eagle.png ${CMAKE_CURRENT_BINARY_DIR}/Textures 
)

