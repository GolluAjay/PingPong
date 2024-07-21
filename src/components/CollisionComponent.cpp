#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(const sf::FloatRect& bounds)
    : bounds(bounds) {}

sf::FloatRect CollisionComponent::getBounds() const {
    return bounds;
}

void CollisionComponent::setBounds(const sf::FloatRect& bounds) {
    this->bounds = bounds;
}
