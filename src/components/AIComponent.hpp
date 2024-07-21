#pragma once
#include "ECS/Component.hpp"
#include <SFML/System/Vector2.hpp>

class AIComponent : public Component
{
public:
    AIComponent(float speed = 0.0f, bool isPaddle = false);

    void setVelocity(const sf::Vector2f &velocity);
    sf::Vector2f getVelocity() const;

    float getSpeed() const;
    bool getIsPaddle() const;

private:
    float speed;  // Speed for paddle movement
    bool isPaddle; // Flag to determine if the entity is a paddle
	 sf::Vector2f velocity;
};
