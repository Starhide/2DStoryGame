#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

namespace textures {
extern std::map<std::string, sf::Texture> loadedTextures;

static sf::Texture *loadTexture(std::string filename) {
    if (loadedTextures.count(filename)) {
        return &loadedTextures[filename];
    }

    sf::Texture newTexture;

    if (!newTexture.loadFromFile(filename.c_str())) {
        std::cout << "@! Could not load " << filename << std::endl;
        return nullptr;
    }

    loadedTextures[filename] = newTexture;
    return &loadedTextures[filename];
}
} //ns end textures