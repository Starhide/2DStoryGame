#include <SFML/Graphics.hpp>
#include "TextureController.h"
#include <iostream>

sf::Texture* textures::loadTexture(std::string filename){
    if(loadedTextures.count(filename)){
        return &loadedTextures[filename];
    }

    sf::Texture newTexture;

    if(!newTexture.loadFromFile(filename.c_str())){
        std::cout << "Could not load " << filename << std::endl;
    }

    loadedTextures[filename] = newTexture;
    return &loadedTextures[filename];
}
