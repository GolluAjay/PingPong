#pragma once
#include "ECS/Component.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class SpriteComponent : public Component
{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    SpriteComponent(const std::string &filePath);
    void setSizeBasedOnWindow(const sf::RenderWindow &window);
    void setSize(float width, float height);
    void setPosition(float x, float y);
    sf::Sprite &getSprite();
};
