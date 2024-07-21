#pragma once
#include "ECS/System.hpp"
#include <vector>
#include <memory>
#include "../ECS/Entity.hpp"

class CollisionSystem  : public System {
public:
    void update(float deltaTime) override;

private:
    void handleCollision(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB);
};
