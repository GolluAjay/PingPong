#pragma once
#include "ECS/Component.hpp"
#include <SFML/System/Vector2.hpp>

class TransformComponent : public Component {
public:
    sf::Vector2f position;

     // Constructor
    TransformComponent(float x = 0, float y = 0);

    // Methods to set and translate position
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
    void translate(float x, float y);
    void translate(const sf::Vector2f& offset);
    sf::Vector2f getPosition() const;
};
