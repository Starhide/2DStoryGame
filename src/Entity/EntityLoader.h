#pragma once

namespace el {

template <typename T>
void addComponent(Entity *e, luabridge::LuaRef &componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(componentTable));
}

Entity *loadEntity(lua_State *L, const std::string &type, const std::string &filename) {
    using namespace luabridge;

    luah::loadScript(L, filename);

    auto e = new Entity();
    e->setType(type);

    auto v = luah::getTableKeys(L, type);
    LuaRef entityTable = getGlobal(L, type.c_str());

    for (auto &componentName : v) {
        if (componentName == "Sprite") {
            LuaRef valueTable = entityTable["Sprite"];
            addComponent<Sprite>(e, valueTable);

        } else if (componentName == "Input") {
            LuaRef valueTable = entityTable["Input"];
            addComponent<Input>(e, valueTable);
            globals::inputlisteners.push_back(e->get<Input>());
        }

        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}

Entity* createEntity(lua_State *L, luabridge::LuaRef &initTable){
    using namespace luabridge;
    LuaRef idLR = initTable["id"];
    std::string id = idLR.cast<std::string>();

    LuaRef posX = initTable["posX"];
    LuaRef posY = initTable["posY"];
    sf::Vector2f position = sf::Vector2f(posX.cast<float>(), posY.cast<float>());

    LuaRef typeLR = initTable["typename"];
    std::string type = typeLR.cast<std::string>();

    LuaRef typefileLR = initTable["typefile"];
    std::string typefile = typefileLR.cast<std::string>();

    LuaRef components = initTable["components"];

    auto newEntity = loadEntity(L, type, typefile); 
    newEntity->setID(id);
    newEntity->setPosition(position);

    auto v = luah::getTableKeys(components);

    for (auto &componentName : v) {
        if (componentName == "Sprite") {
            LuaRef spriteTable = components["Sprite"];
            newEntity->get<Sprite>()->setAttributes(spriteTable);
        } else if (componentName == "Input") {
            LuaRef spriteTable = components["Input"];
            newEntity->get<Input>()->setAttributes(spriteTable);
        }

        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return newEntity;
}

} //el 