#pragma once
#include "ECS/System.hpp"
#include <SFML/Graphics.hpp>

class RenderSystem : public System {
public:
    void render(sf::RenderWindow& window);
    void update(float deltaTime) override;
};