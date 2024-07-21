#pragma once
#include "ECS/Component.hpp"
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

class InputComponent : public Component {
public:
    std::unordered_map<sf::Keyboard::Key, bool> keyMap;

    bool isKeyPressed(sf::Keyboard::Key key) const {
        auto it = keyMap.find(key);
        if (it != keyMap.end()) {
            return it->second;
        }
        return false;
    }

    void setKey(sf::Keyboard::Key key, bool pressed) {
        keyMap[key] = pressed;
    }
};
