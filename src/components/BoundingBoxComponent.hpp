#pragma once
#include "ECS/Component.hpp"
#include <SFML/System/Vector2.hpp>

class BoundingBoxComponent : public Component {
public:
    sf::Vector2f min;
    sf::Vector2f max;

    BoundingBoxComponent(const sf::Vector2f& min, const sf::Vector2f& max)
        : min(min), max(max) {}
};
