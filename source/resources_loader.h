#ifndef GAME_OF_LIFE_RESOURCES_LOADER_H
#define GAME_OF_LIFE_RESOURCES_LOADER_H

#include <SFML/Graphics.hpp>
#include <filesystem>

bool load_font(const std::string &font_name, sf::Font &font, const uint8_t &number_of_tries = 10) {
    std::string path = "../fonts/" + font_name;
    std::filesystem::path source_path = std::filesystem::path(__FILE__).parent_path();
    std::filesystem::path font_path = source_path / path;

    uint8_t try_number = 1;

    do {
        std::cout << "Loading font:\nPath: " << path <<
                  "\nTry: " + std::to_string(try_number) << "/" <<
                  std::to_string(number_of_tries) << std::endl;

        if (font.loadFromFile(font_path.string())) {
            std::cout << "Status: success" << std::endl;
            return true;
        } else {
            std::cout << "Status: error" << std::endl;
            path.push_back('/');
            path.push_back('.');
            path.push_back('.');
            font_path = source_path / path;
            try_number++;
        }
    } while (try_number <= number_of_tries);

    return false;
}

#endif
