#include "game_of_life_algorithm.h"

void game_of_life_algorithm::prepare_for_drawing() {
    if (_cells == nullptr) {
        return;
    }

    for (uint32_t cell_y = 0; cell_y < _game_of_life_height; ++cell_y) {
        for (uint32_t cell_x = 0; cell_x < _game_of_life_width; ++cell_x) {
            sf::Color cell_color = _cells[cell_y][cell_x] ? _alive_cell_color : _dead_cell_color;
            sf::Color fill_color = cell_y == _selected_cell.y &&
                                   cell_x == _selected_cell.x ? _selection_color : _grid_color;


            uint32_t pixel_y, pixel_x;

            for (pixel_y = cell_y * _cell_size;
                 pixel_y < cell_y * _cell_size + _cell_size;
                 ++pixel_y) {
                for (pixel_x = cell_x * _cell_size;
                     pixel_x < cell_x * _cell_size + _cell_size;
                     ++pixel_x) {
                    _cells_image.setPixel(pixel_x, pixel_y, fill_color);
                }
            }

            for (pixel_y = cell_y * _cell_size + _selection_size;
                 pixel_y < cell_y * _cell_size + _cell_size - _selection_size;
                 ++pixel_y) {
                for (pixel_x = cell_x * _cell_size + _selection_size;
                     pixel_x < cell_x * _cell_size + _cell_size - _selection_size;
                     ++pixel_x) {
                    _cells_image.setPixel(pixel_x, pixel_y, cell_color);
                }
            }


        }
    }

    _cells_texture.update(_cells_image);
    _cells_sprite.setTexture(_cells_texture);
}

uint8_t game_of_life_algorithm::calculate_neighbors(const uint32_t &cell_x,
                                                    const uint32_t &cell_y,
                                                    bool **cells) const {
    uint8_t neighbors = 0;

    const uint32_t START_X = cell_x >= 1 ? cell_x - 1 : cell_x;
    const uint32_t START_Y = cell_y >= 1 ? cell_y - 1 : cell_y;
    const uint32_t LIMIT_X = cell_x + 1 < _game_of_life_width ? cell_x + 1 : cell_x;
    const uint32_t LIMIT_Y = cell_y + 1 < _game_of_life_height ? cell_y + 1 : cell_y;

    for (uint32_t y = START_Y; y <= LIMIT_Y; ++y) {
        for (uint32_t x = START_X; x <= LIMIT_X; ++x) {
            if (cells[y][x]) {
                neighbors++;
            }
        }
    }

    if (cells[cell_y][cell_x] && neighbors > 0) {
        --neighbors;
    }

    return neighbors;
}

[[maybe_unused]] game_of_life_algorithm::game_of_life_algorithm(const uint32_t &screen_width,
                                                                const uint32_t &screen_height,
                                                                const uint32_t &cell_size) {
    _screen_width = screen_width;
    _screen_height = screen_height;

    _cell_size = cell_size;

    _game_of_life_width = _screen_width / _cell_size;
    _game_of_life_height = _screen_height / _cell_size;

    _cells = new bool *[_game_of_life_height];
    for (uint32_t y = 0; y < _game_of_life_height; ++y) {
        _cells[y] = new bool[_game_of_life_width];
        for (uint32_t x = 0; x < _game_of_life_width; ++x) {
            _cells[y][x] = DEAD;
        }
    }

    _cells_image.create(_screen_width, _screen_height, _dead_cell_color);
    _cells_texture.create(_screen_width, _screen_height);
}

game_of_life_algorithm::~game_of_life_algorithm() {
    for (uint32_t y = 0; y < _game_of_life_height; ++y) {
        delete[] _cells[y];
    }

    delete[] _cells;
}

[[maybe_unused]] void game_of_life_algorithm::generate_new_generation() {
    bool **previous_cells_state = new bool *[_game_of_life_height];
    for (uint32_t y = 0; y < _game_of_life_height; ++y) {
        previous_cells_state[y] = new bool[_game_of_life_width];
        for (uint32_t x = 0; x < _game_of_life_width; ++x) {
            previous_cells_state[y][x] = _cells[y][x];
        }
    }

    for (uint32_t cell_y = 0; cell_y < _game_of_life_height; ++cell_y) {
        for (uint32_t cell_x = 0; cell_x < _game_of_life_width; ++cell_x) {
            uint8_t cell_neighbors = calculate_neighbors(cell_x, cell_y, previous_cells_state);

            if (cell_neighbors < _underpopulation || cell_neighbors > _overpopulation) {
                _cells[cell_y][cell_x] = DEAD;
            } else if (cell_neighbors == _reproduction) {
                _cells[cell_y][cell_x] = ALIVE;
            }
        }
    }

    for (uint32_t y = 0; y < _game_of_life_height; ++y) {
        delete[] previous_cells_state[y];
    }

    delete[] previous_cells_state;
}


[[maybe_unused]] void game_of_life_algorithm::start_generating_new_generations() {
    _is_running = true;
}

[[maybe_unused]] void game_of_life_algorithm::stop_generation_new_generations() {
    _is_running = false;
}

[[maybe_unused]] void game_of_life_algorithm::update(sf::RenderWindow &window, sf::Event &event) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    _selected_cell.x = mouse_position.x / _cell_size;
    _selected_cell.y = mouse_position.y / _cell_size;

    bool is_drawing_cells = false;

    if (_selected_cell.x >= 0 &&
        _selected_cell.y >= 0 &&
        _selected_cell.x < _game_of_life_width &&
        _selected_cell.y < _game_of_life_height) {

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            is_drawing_cells = true;
            _elapsed_time = sf::Time::Zero;
            _cells[_selected_cell.y][_selected_cell.x] = ALIVE;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            is_drawing_cells = true;
            _elapsed_time = sf::Time::Zero;
            _cells[_selected_cell.y][_selected_cell.x] = DEAD;
        } else {
            is_drawing_cells = false;
        }
    }

    if (event.key.code == sf::Keyboard::Key::Space) {
        _is_running = !_is_running;
    } else if (event.key.code == sf::Keyboard::Key::C) {
        clear();
        _generations_count = 0;
    }

    if (_is_running && !is_drawing_cells) {
        _elapsed_time += _clock.restart();
    }

    if (_elapsed_time >= _delay) {
        _elapsed_time = sf::Time::Zero;
        generate_new_generation();
        _generations_count++;
    }
}

[[maybe_unused]] void game_of_life_algorithm::draw_cells(sf::RenderWindow &window) {
    prepare_for_drawing();
    window.draw(_cells_sprite);
}

void game_of_life_algorithm::clear() {
    for (uint32_t cell_y = 0; cell_y < _game_of_life_height; ++cell_y) {
        for (uint32_t cell_x = 0; cell_x < _game_of_life_width; ++cell_x) {
            _cells[cell_y][cell_x] = DEAD;
        }
    }
}

[[maybe_unused]] void game_of_life_algorithm::set_underpopulation(const uint8_t &value) {
    _underpopulation = value;
}

[[maybe_unused]] void game_of_life_algorithm::set_overpopulation(const uint8_t &value) {
    _overpopulation = value;
}

[[maybe_unused]] void game_of_life_algorithm::set_reproduction(const uint8_t &value) {
    _reproduction = value;
}

[[maybe_unused]] void game_of_life_algorithm::set_selection_size(const uint32_t &value) {
    _selection_size = value;
}

[[maybe_unused]] void game_of_life_algorithm::set_delay(const float &value) {
    _delay = sf::seconds(value);
}

[[maybe_unused]] void game_of_life_algorithm::set_dead_cell_color(const sf::Color &color) {
    _dead_cell_color = color;
}

[[maybe_unused]] void game_of_life_algorithm::set_alive_cell_color(const sf::Color &color) {
    _alive_cell_color = color;
}

[[maybe_unused]] void game_of_life_algorithm::set_selection_color(const sf::Color &color) {
    _selection_color = color;
}

[[maybe_unused]] void game_of_life_algorithm::set_grid_color(const sf::Color &color) {
    _grid_color = color;
}

[[maybe_unused]] uint32_t game_of_life_algorithm::get_generations_count() const {
    return _generations_count;
}

[[maybe_unused]] sf::Vector2<uint32_t> game_of_life_algorithm::get_selected_cell_position() {
    if (_selected_cell.x >= 0 &&
        _selected_cell.y >= 0 &&
        _selected_cell.x < _game_of_life_width &&
        _selected_cell.y < _game_of_life_height) {
        return _selected_cell;
    }

    return {0, 0};
}
