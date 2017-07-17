#include <SFML/Graphics.hpp>

#include "Graphics.h"

Graphics::Graphics(sol::table &componentTable) {
    this->sprite = sf::Sprite();

    sol::object filenameRef = componentTable["filename"];
    if (filenameRef.valid()) {
        std::string file = filenameRef.as<std::string>();
        sf::Texture *text = textures::loadTexture(file);
        if (!(text == nullptr)) {
            this->sprite.setTexture(*text);
        } else {
            std::cout << "@! " << file
                      << " failed to load in Graphics Component." << std::endl;
        }
    } else {
        std::cout << "@! Filename is not a string in Graphics Component."
                  << std::endl;
    }

    bool setup = componentTable["no_animation"].get_or(false);

    if (setup) {
        sequences["idle"] = std::vector<int> {0};
        sequence = "idle";
        scale = 1;
        size = sprite.getTexture()->getSize().x / scale;
        rate = 0;
        isRunning = false;
        
    } else {
        sol::table sequencesT = componentTable["sequences"];

        for (auto &kvp : sequencesT) {
            std::string key = kvp.first.as<std::string>();
            sol::table value = kvp.second;
            std::vector<int> seq;

            for (unsigned int i = 1; i <= value.size(); i++) {
                seq.push_back(value[i]);
            }

            sequences[key] = seq;
        }

        scale = componentTable["scale"];
        size = sprite.getTexture()->getSize().x / scale;

        rate = componentTable["rate"].get_or(0.0f);
        sequence = componentTable["startSequence"];
        index = componentTable["startIndex"].get_or(0);
        isRunning = componentTable["isRunning"].get_or(false);
    }

    setTextureRect();
}

void Graphics::setAttributes(sol::table &table) {
    std::string temp = table["startSequence"].get_or(std::string("null"));
    if (temp != "null") {
        sequence = temp;
    }

    int temp2 = table["startIndex"].get_or(-1);
    if (temp2 != -1)
        index = table["startIndex"];

    isRunning = table["isRunning"].get_or(false);
}

void Graphics::drawUpdate(Entity *e, sf::RenderWindow &win) {
    sprite.setPosition(e->getPosition());
    sprite.setRotation(e->getRotation());
    sprite.setScale(e->getScale());
    win.draw(sprite);
}

void Graphics::fixedUpdate(Entity *e) {
    if (isRunning) {
        if (timer.getElapsedTime().asSeconds() > rate) {
            index++;

            if (index >= sequences[sequence].size()) {
                index = 0;
            }

            setTextureRect();

            timer.restart();
        }
    }
}

void Graphics::stop() {
    isRunning = false;
    index = 0;
    setTextureRect();
}

void Graphics::run(std::string seq) {
    sequence = seq;
    isRunning = true;
}

void Graphics::setCurrent(std::string seq, int index) {
    this->sequence = seq;
    this->index = index;
    setTextureRect();
}