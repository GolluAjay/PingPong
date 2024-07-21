#include "TransformComponent.hpp"

// Constructor
TransformComponent::TransformComponent(float x, float y) : position(x, y) {}

// Set position using float values
void TransformComponent::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

// Set position using a vector
void TransformComponent::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

// Translate position using float values
void TransformComponent::translate(float x, float y) {
    position.x += x;
    position.y += y;
}

// Translate position using a vector
void TransformComponent::translate(const sf::Vector2f& offset) {
    position += offset;
}

// Get the current position
sf::Vector2f TransformComponent::getPosition() const {
    return position;
}
