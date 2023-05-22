#ifndef GAME_OF_LIFE_RESOURCES_LOADER_H
#define GAME_OF_LIFE_RESOURCES_LOADER_H

#include <SFML/Graphics.hpp>
#include <filesystem>

bool load_font(const std::string &path, sf::Font &font) {
    std::filesystem::path source_path = std::filesystem::path(__FILE__).parent_path();
    std::filesystem::path font_path = source_path / path;
    return font.loadFromFile(font_path.string());
}

#endif
