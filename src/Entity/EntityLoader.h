#pragma once

namespace el {

Entity *loadEntity(std::map<std::string, sol::table> &components,
                   sol::table &pattern, sol::table &init) {

    auto e = new Entity();
    e->setID(init["id"]);
    sol::table t = pattern;
    sol::table comps = init["components"];

    for (auto &kvp : comps) {
        for (auto &kvp2 : kvp.second.as<sol::table>()) {
            t[kvp.first][kvp2.first] = kvp2.second;
        }
    }

    std::string key;

    for (auto &kvp : t) {
        key = kvp.first.as<std::string>();
        e->addComponent(
            key, components[key]["new"](components[key], *e, kvp.second));
        std::cout << "Added " << key << " to " << std::endl;
    }

    return e;
}

} // el