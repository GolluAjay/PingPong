#include "RenderSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

void RenderSystem::render(sf::RenderWindow &window)
{
    for (auto &entity : entities)
    {
        auto spriteComponent = entity->getComponent<SpriteComponent>();
        auto transformComponent = entity->getComponent<TransformComponent>();
        if (spriteComponent && transformComponent)
        {
            spriteComponent->sprite.setPosition(transformComponent->position);
            window.draw(spriteComponent->sprite);
        }
    }
}

void RenderSystem::update(float deltaTime)
{
    (void)deltaTime; // Suppress unused parameter warning
    // Future animation update logic can use deltaTime here
}