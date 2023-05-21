#include <SFML/Graphics.hpp>
#include "game_of_life_algorithm.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    const uint32_t WINDOW_WIDTH = 1200;
    const uint32_t WINDOW_HEIGHT = 800;

    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT},
                            "Game Of Life",
                            sf::Style::Close,
                            settings);

    game_of_life_algorithm game_of_life(WINDOW_WIDTH, WINDOW_HEIGHT, 20);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }
        }

        game_of_life.update(window, event);

        window.clear(sf::Color::Black);
        game_of_life.draw_cells(window);
        window.display();
    }

    return 0;
}
