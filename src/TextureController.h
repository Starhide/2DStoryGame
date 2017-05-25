#pragma once

#include <map>
#include <string>

namespace sf{
    class Texture;
}

namespace textures{
    extern std::map<std::string, sf::Texture> loadedTextures;

    sf::Texture* loadTexture(std::string filename);
}