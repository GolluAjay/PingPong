#pragma once
#include "ECS/Component.hpp"
#include <SFML/Graphics/Rect.hpp>

class CollisionComponent : public Component {
public:
    CollisionComponent(const sf::FloatRect& bounds);

    sf::FloatRect getBounds() const;
    void setBounds(const sf::FloatRect& bounds);

private:
    sf::FloatRect bounds;
};
