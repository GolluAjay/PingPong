#include "Utils.hpp"

void centerSpriteInWindow(std::shared_ptr<SpriteComponent> sprite, const sf::RenderWindow& window, std::shared_ptr<TransformComponent> transform) {
    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect spriteBounds = sprite->sprite.getLocalBounds();

    // Calculate the center position
    float centerX = (windowSize.x - spriteBounds.width) / 2.0f;
    float centerY = (windowSize.y - spriteBounds.height) / 2.0f;

    // Set the position of the transform component
    transform->setPosition(centerX, centerY);

    // Apply the position to the sprite
    sprite->setPosition(transform->getPosition().x, transform->getPosition().y);
}

void clampToBounds(std::shared_ptr<SpriteComponent> sprite, std::shared_ptr<TransformComponent> transform, const std::shared_ptr<BoundingBoxComponent>& boundingBox) {
    sf::FloatRect spriteBounds = sprite->sprite.getGlobalBounds();

    // Clamp the position to keep the sprite within the bounding box
    sf::Vector2f position = transform->getPosition();
    position.x = std::max(boundingBox->min.x, std::min(position.x, boundingBox->max.x - spriteBounds.width));
    position.y = std::max(boundingBox->min.y, std::min(position.y, boundingBox->max.y - spriteBounds.height));

    // Set the clamped position
    transform->setPosition(position.x, position.y);
    sprite->sprite.setPosition(position);
}
