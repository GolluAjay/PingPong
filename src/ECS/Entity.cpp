#include "Entity.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/AIComponent.hpp"

void Entity::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

// Explicit instantiation for common components
template std::shared_ptr<TransformComponent> Entity::getComponent<TransformComponent>();
template std::shared_ptr<SpriteComponent> Entity::getComponent<SpriteComponent>();
template std::shared_ptr<CollisionComponent> Entity::getComponent<CollisionComponent>();
template std::shared_ptr<BoundingBoxComponent> Entity::getComponent<BoundingBoxComponent>();
template std::shared_ptr<InputComponent> Entity::getComponent<InputComponent>();
template std::shared_ptr<AIComponent> Entity::getComponent<AIComponent>();