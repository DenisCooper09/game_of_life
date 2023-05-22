set(SOURCES
        main.cpp
        game_of_life_algorithm.cpp
        game_of_life_algorithm.h
        resources_loader.h
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(game_of_life PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        )
