#include "CollisionSystem.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/CollisionComponent.hpp"
#include "../components/AIComponent.hpp"
#include "../components/InputComponent.hpp"
#include <cmath>

void CollisionSystem::update(float deltaTime) {
    (void)deltaTime;
    for (size_t i = 0; i < entities.size(); ++i) {
        auto entityA = entities[i];
        auto transformA = entityA->getComponent<TransformComponent>();
        auto collisionA = entityA->getComponent<CollisionComponent>();

        if (transformA && collisionA) {
            sf::FloatRect boundsA = collisionA->getBounds();
            boundsA.left += transformA->position.x;
            boundsA.top += transformA->position.y;

            for (size_t j = i + 1; j < entities.size(); ++j) {
                auto entityB = entities[j];
                auto transformB = entityB->getComponent<TransformComponent>();
                auto collisionB = entityB->getComponent<CollisionComponent>();

                if (transformB && collisionB) {
                    sf::FloatRect boundsB = collisionB->getBounds();
                    boundsB.left += transformB->position.x;
                    boundsB.top += transformB->position.y;

                    if (boundsA.intersects(boundsB)) {
                        handleCollision(entityA, entityB);
                    }
                }
            }
        }
    }
}

void CollisionSystem::handleCollision(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB) {
    auto transformA = entityA->getComponent<TransformComponent>();
    auto transformB = entityB->getComponent<TransformComponent>();
    auto aiA = entityA->getComponent<AIComponent>();
    auto aiB = entityB->getComponent<AIComponent>();

    if (transformA && transformB) {
        sf::FloatRect boundsA = entityA->getComponent<CollisionComponent>()->getBounds();
        sf::FloatRect boundsB = entityB->getComponent<CollisionComponent>()->getBounds();

        // Adjust bounds by the entity's position
        boundsA.left += transformA->position.x;
        boundsA.top += transformA->position.y;
        boundsB.left += transformB->position.x;
        boundsB.top += transformB->position.y;

        // Calculate intersection depth
        float overlapLeft = (boundsA.left + boundsA.width) - boundsB.left;
        float overlapRight = (boundsB.left + boundsB.width) - boundsA.left;
        float overlapTop = (boundsA.top + boundsA.height) - boundsB.top;
        float overlapBottom = (boundsB.top + boundsB.height) - boundsA.top;

        // Find the minimum depth
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        float correctionFactor = 0.5f; // Adjust based on your needs

        auto reflectVelocity = [](std::shared_ptr<AIComponent> ai, bool reflectX, bool reflectY) {
            sf::Vector2f newVelocity = ai->getVelocity();
            if (reflectX) newVelocity.x = -newVelocity.x;
            if (reflectY) newVelocity.y = -newVelocity.y;
            ai->setVelocity(newVelocity);
        };

        // If entityA is the ball
        if (aiA && !aiA->getIsPaddle() && !entityA->getComponent<InputComponent>()) {
            if (minOverlapX < minOverlapY) {
                // Horizontal collision
                if (overlapLeft < overlapRight) {
                    // Collision on the left side of the paddle
                    transformA->position.x -= overlapLeft * correctionFactor;
                } else {
                    // Collision on the right side of the paddle
                    transformA->position.x += overlapRight * correctionFactor;
                }
                reflectVelocity(aiA, true, false);
            } else {
                // Vertical collision
                if (overlapTop < overlapBottom) {
                    // Collision on the top side of the paddle
                    transformA->position.y -= overlapTop * correctionFactor;
                } else {
                    // Collision on the bottom side of the paddle
                    transformA->position.y += overlapBottom * correctionFactor;
                }
                reflectVelocity(aiA, false, true);
            }
        }
        // If entityB is the ball
        else if (aiB && !entityB->getComponent<InputComponent>()) {
            if (minOverlapX < minOverlapY) {
                // Horizontal collision
                if (overlapLeft < overlapRight) {
                    // Collision on the left side of the paddle
                    transformB->position.x -= overlapLeft * correctionFactor;
                } else {
                    // Collision on the right side of the paddle
                    transformB->position.x += overlapRight * correctionFactor;
                }
                reflectVelocity(aiB, true, false);
            } else {
                // Vertical collision
                if (overlapTop < overlapBottom) {
                    // Collision on the top side of the paddle
                    transformB->position.y -= overlapTop * correctionFactor;
                } else {
                    // Collision on the bottom side of the paddle
                    transformB->position.y += overlapBottom * correctionFactor;
                }
                reflectVelocity(aiB, false, true);
            }
        }
    }
}
