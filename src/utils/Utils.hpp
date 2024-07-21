#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/BoundingBoxComponent.hpp"

void centerSpriteInWindow(std::shared_ptr<SpriteComponent> sprite, const sf::RenderWindow& window, std::shared_ptr<TransformComponent> transform);
void clampToBounds(std::shared_ptr<SpriteComponent> sprite, std::shared_ptr<TransformComponent> transform,const std::shared_ptr<BoundingBoxComponent>& boundingBox);
