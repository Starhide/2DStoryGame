#pragma once

namespace el {

template <typename T>
void addComponent(Entity *e, sol::table &componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(componentTable));
}

Entity *loadEntity(sol::state &lua, const std::string &type,
                   const std::string &filename) {

    lua.script_file(filename);

    auto e = new Entity();
    e->setType(type);
    std::string key;
    sol::table tabs = lua[type];

    for (auto& kvp : tabs) {
        key = kvp.first.as<std::string>();
        if (key == "Sprite") {
            sol::table valueTable = lua[type]["Sprite"];
            addComponent<Sprite>(e, valueTable);

        } else if (key == "Input") {
            sol::table valueTable = lua[type]["Input"];
            addComponent<Input>(e, valueTable);
            globals::inputlisteners.push_back(e->get<Input>());
        }

        std::cout << "Added " << key << " to " << type << std::endl;
    }
    return e;
}

Entity *createEntity(sol::state &lua, sol::table &initTable) {
    std::string id = initTable["id"];
    sf::Vector2f position =
        sf::Vector2f(initTable["posX"], initTable["posY"]);
    std::string type = initTable["typename"];
    std::string typefile = initTable["typefile"];

    sol::table components = initTable["components"];

    auto newEntity = loadEntity(lua, type, typefile);
    newEntity->setID(id);
    newEntity->setPosition(position);

    std::string key;
    for (auto& kvp : components) {
        key = kvp.first.as<std::string>();
        if (key == "Sprite") {
            sol::table valueTable = lua[type]["Sprite"];
           newEntity->get<Sprite>()->setAttributes(valueTable);

        } else if (key == "Input") {
            sol::table valueTable = lua[type]["Input"];
            newEntity->get<Input>()->setAttributes(valueTable);
        }

        std::cout << "Applyed " << key << " to " << id << std::endl;
    }
    return newEntity;
}

} // el