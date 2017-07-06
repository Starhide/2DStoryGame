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

    sol::table sequencesT = componentTable["sequences"];

    for (auto &kvp : sequencesT) {
        std::string key = kvp.first.as<std::string>();
        sol::table value = kvp.second;
        int row = value[1];
        std::vector<int> seq;
        
        for (unsigned int i = 2; i <= value.size(); i++) {
            seq.push_back(value[i]);
        }

        Animation temp;
        temp.row = row;
        temp.sequence = seq;
        sequences[key] = temp;
    }

    size = componentTable["size"];
    rate = componentTable["rate"];
    setAttributes(componentTable);

    Animation curr = sequences[sequence];
    sprite.setTextureRect(
        sf::IntRect(curr.sequence[index] * size, curr.row * size, size, size));
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
            Animation curr = sequences[sequence];

            if(index >= curr.sequence.size()){
                index = 0;
            }

            sprite.setTextureRect(sf::IntRect(curr.sequence[index] * size,
                                              curr.row * size, size, size));

            timer.restart();
        }
    }
   
}

void Graphics::stop() {
    isRunning = false;
    index = 0;
    Animation curr = sequences[sequence];
    sprite.setTextureRect(
        sf::IntRect(curr.sequence[index] * size, curr.row * size, size, size));
}

void Graphics::run(std::string seq) {
    sequence = seq;
    isRunning = true;
}

void Graphics::setCurrent(std::string seq, int index) {
    this->sequence = seq;
    this->index = index;
    Animation curr = sequences[sequence];
    sprite.setTextureRect(
        sf::IntRect(curr.sequence[index] * size, curr.row * size, size, size));
}