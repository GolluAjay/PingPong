#pragma once
#include "ECS/System.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../ECS/Entity.hpp"

class AISystem  : public System {
public:
    void update(float deltaTime) override;
    void update(float deltaTime, sf::RenderWindow& window,std::shared_ptr<Entity> ball);
};
