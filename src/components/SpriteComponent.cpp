#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        // Handle error
    }
    sprite.setTexture(texture);
}

void SpriteComponent::setSizeBasedOnWindow(const sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = texture.getSize();

    // Calculate scale factors
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Apply the scale to the sprite (this example assumes you want to scale proportionally)
    sprite.setScale(scaleX, scaleY);
}

void SpriteComponent::setSize(float width, float height) {
    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale(width / textureSize.x, height / textureSize.y);
}

void SpriteComponent::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Sprite& SpriteComponent::getSprite() {
    return sprite;
}
