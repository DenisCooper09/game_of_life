#ifndef GAME_OF_LIFE_GAME_OF_LIFE_ALGORITHM_H
#define GAME_OF_LIFE_GAME_OF_LIFE_ALGORITHM_H

#include <SFML/Graphics.hpp>

#define DEAD 0
#define ALIVE 1

#define DEFAULT_UNDERPOPULATION 2
#define DEFAULT_OVERPOPULATION 3
#define DEFAULT_REPRODUCTION 3

class [[maybe_unused]] game_of_life_algorithm {
private:
    uint32_t _screen_width;
    uint32_t _screen_height;

    uint32_t _cell_size;

    uint32_t _game_of_life_width;
    uint32_t _game_of_life_height;

    bool **_cells;

    sf::Vector2<uint32_t> _selected_cell;

    uint8_t _underpopulation = DEFAULT_UNDERPOPULATION;
    uint8_t _overpopulation = DEFAULT_OVERPOPULATION;
    uint8_t _reproduction = DEFAULT_REPRODUCTION;

    sf::Clock _clock;
    sf::Time _delay = sf::seconds(0.5f);
    sf::Time _elapsed_time = sf::Time::Zero;

    bool _is_running = false;

    sf::Image _cells_image;
    sf::Texture _cells_texture;
    sf::Sprite _cells_sprite;

    sf::Color _dead_cell_color = sf::Color::Black;
    sf::Color _alive_cell_color = sf::Color::Green;
    sf::Color _selection_color = sf::Color::White;
    sf::Color _grid_color = sf::Color(30, 30, 30);

    uint32_t _selection_size = 1;

    void prepare_for_drawing();

    uint8_t calculate_neighbors(const uint32_t &cell_x,
                                const uint32_t &cell_y,
                                bool **cells) const;

public:
    [[maybe_unused]] game_of_life_algorithm(const uint32_t &screen_width,
                                            const uint32_t &screen_height,
                                            const uint32_t &cell_size);

    ~game_of_life_algorithm();

    [[maybe_unused]] void update(sf::RenderWindow &window, sf::Event &event);

    [[maybe_unused]] void generate_new_generation();

    [[maybe_unused]] void start_generating_new_generations();

    [[maybe_unused]] void stop_generation_new_generations();

    [[maybe_unused]] void draw_cells(sf::RenderWindow &window);

    void clear();

    [[maybe_unused]] void set_underpopulation(const uint8_t &value);

    [[maybe_unused]] void set_overpopulation(const uint8_t &value);

    [[maybe_unused]] void set_reproduction(const uint8_t &value);

    [[maybe_unused]] void set_selection_size(const uint32_t &value);

    [[maybe_unused]] void set_delay(const float &value);

    [[maybe_unused]] void set_dead_cell_color(const sf::Color &color);

    [[maybe_unused]] void set_alive_cell_color(const sf::Color &color);

    [[maybe_unused]] void set_selection_color(const sf::Color &color);

    [[maybe_unused]] void set_grid_color(const sf::Color &color);
};

#endif
