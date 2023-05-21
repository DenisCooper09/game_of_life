set(SOURCES
        main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(game_of_life PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        )
