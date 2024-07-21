#pragma once
#include "ECS/System.hpp"
#include <SFML/Graphics.hpp>

class InputSystem : public System
{
public:
    void update(float deltaTime) override;
};
