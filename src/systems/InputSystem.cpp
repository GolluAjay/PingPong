#include "InputSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "components/InputComponent.hpp"
#include "../utils/Utils.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

void InputSystem::update(float deltaTime)
{
    for (auto &entity : entities)
    {
        auto transformComponent = entity->getComponent<TransformComponent>();
        auto spriteComponent = entity->getComponent<SpriteComponent>();
        auto boundingBoxComponent = entity->getComponent<BoundingBoxComponent>();
        auto inputComponent = entity->getComponent<InputComponent>();

        if (transformComponent && inputComponent)
        {
            float speed = 300.0f; // Speed in pixels per second

            if (inputComponent->isKeyPressed(sf::Keyboard::Up))
            {
                transformComponent->position.y -= speed * deltaTime;
            }
            if (inputComponent->isKeyPressed(sf::Keyboard::Down))
            {
                transformComponent->position.y += speed * deltaTime;
            }
            if (inputComponent->isKeyPressed(sf::Keyboard::Left))
            {
                transformComponent->position.x -= speed * deltaTime;
            }
            if (inputComponent->isKeyPressed(sf::Keyboard::Right))
            {
                transformComponent->position.x += speed * deltaTime;
            }
        }

        if (boundingBoxComponent && spriteComponent)
        {
            // Clamp the new position to keep the sprite within the bounding box
            clampToBounds(spriteComponent, transformComponent, boundingBoxComponent);
        }
    }
}
