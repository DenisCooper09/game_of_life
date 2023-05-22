#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "game_of_life_algorithm.h"
#include "resources_loader.h"

template<typename T>
std::string to_string_with_precision(const T &value, const int &n = 1) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << value;
    return std::move(out).str();
}

int main() {
    sf::Font main_font;
    if (!load_font("../fonts/Roboto-Regular.ttf", main_font)) {
        std::cout << "The font could not be loaded properly.";
        system("pause>nul");
        return -1;
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    const uint32_t WINDOW_WIDTH = 1200;
    const uint32_t WINDOW_HEIGHT = 800;

    float generations_per_second = 1.0f;

    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT},
                            "Game Of Life",
                            sf::Style::Close,
                            settings);

    sf::Text generations_count_text;
    generations_count_text.setFont(main_font);
    generations_count_text.setFillColor(sf::Color::Green);
    generations_count_text.setPosition(WINDOW_HEIGHT + 15, 10);
    generations_count_text.setCharacterSize(24);

    sf::Text generations_per_second_text;
    generations_per_second_text.setFont(main_font);
    generations_per_second_text.setFillColor(sf::Color::Green);
    generations_per_second_text.setPosition(WINDOW_HEIGHT + 15, 50);
    generations_per_second_text.setCharacterSize(24);

    sf::Text selected_cell_position_text;
    selected_cell_position_text.setFont(main_font);
    selected_cell_position_text.setFillColor(sf::Color::Green);
    selected_cell_position_text.setPosition(WINDOW_HEIGHT + 15, 90);
    selected_cell_position_text.setCharacterSize(24);

    sf::Text selected_cell_state_text;
    selected_cell_state_text.setFont(main_font);
    selected_cell_state_text.setFillColor(sf::Color::Green);
    selected_cell_state_text.setPosition(WINDOW_HEIGHT + 15, 130);
    selected_cell_state_text.setCharacterSize(24);

    sf::Text selected_cell_neighbors_count;
    selected_cell_neighbors_count.setFont(main_font);
    selected_cell_neighbors_count.setFillColor(sf::Color::Green);
    selected_cell_neighbors_count.setPosition(WINDOW_HEIGHT + 15, 170);
    selected_cell_neighbors_count.setCharacterSize(24);

    game_of_life_algorithm game_of_life(WINDOW_HEIGHT, WINDOW_HEIGHT, 20);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            } else if (event.type == sf::Event::EventType::MouseWheelScrolled) {
                generations_per_second += event.mouseWheelScroll.delta / 2.0f;
                if (generations_per_second > 20.0f) {
                    generations_per_second = 1.0f;
                } else if (generations_per_second <= 0.0f) {
                    generations_per_second = 20.0f;
                }
            }
        }

        game_of_life.update(window, event);
        game_of_life.set_delay(1.0f / generations_per_second);

        generations_count_text.setString(
                "Generation: " + std::to_string(game_of_life.get_generations_count())
        );

        generations_per_second_text.setString(
                "Generations/second: " + to_string_with_precision(generations_per_second)
        );

        selected_cell_position_text.setString(
                "X: " + std::to_string(game_of_life.get_selected_cell_position().x) +
                " Y: " + std::to_string(game_of_life.get_selected_cell_position().y)
        );

        selected_cell_state_text.setString((game_of_life.get_cell(
                game_of_life.get_selected_cell_position().x,
                game_of_life.get_selected_cell_position().y) ? "ALIVE" : "DEAD")
        );

        selected_cell_neighbors_count.setString(
                "Neighbors: " + std::to_string(game_of_life.calculate_neighbors(
                        game_of_life.get_selected_cell_position().x,
                        game_of_life.get_selected_cell_position().y
                ))
        );

        window.clear(sf::Color::Black);

        game_of_life.draw_cells(window);

        window.draw(generations_count_text);
        window.draw(generations_per_second_text);
        window.draw(selected_cell_position_text);
        window.draw(selected_cell_state_text);
        window.draw(selected_cell_neighbors_count);

        window.display();
    }

    return 0;
}
