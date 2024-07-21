#include "AISystem.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/AIComponent.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstdlib> // For std::rand and std::srand
#include <ctime>   // For std::time

void AISystem::update(float deltaTime)
{
    (void)deltaTime; // Suppress unused parameter warning
    // Future animation update logic can use deltaTime here
}

void AISystem::update(float deltaTime, sf::RenderWindow &window, std::shared_ptr<Entity> ball)
{
	auto ballTransform = ball->getComponent<TransformComponent>();

	for (auto &entity : entities)
	{
		auto transformComponent = entity->getComponent<TransformComponent>();
		auto aiComponent = entity->getComponent<AIComponent>();
		auto spriteComponent = entity->getComponent<SpriteComponent>();

		if (transformComponent && aiComponent && spriteComponent)
		{
			if (aiComponent->getIsPaddle())
			{
				// AI Paddle logic
                if (ballTransform)
                {
                    // Make the paddle follow the ball's y position
                    float ballY = ballTransform->position.y;
                    float paddleY = transformComponent->position.y;
                    float paddleHeight = spriteComponent->sprite.getGlobalBounds().height;

                    // Simple AI to follow the ball
                    if (ballY < paddleY)
                    {
                        transformComponent->position.y -= aiComponent->getSpeed() * deltaTime;
                    }
                    else if (ballY + paddleHeight > paddleY + paddleHeight)
                    {
                        transformComponent->position.y += aiComponent->getSpeed() * deltaTime;
                    }

                    // Ensure the paddle stays within the window boundaries
                    if (transformComponent->position.y < 0)
                    {
                        transformComponent->position.y = 0;
                    }
                    if (transformComponent->position.y + paddleHeight > window.getSize().y)
                    {
                        transformComponent->position.y = window.getSize().y - paddleHeight;
                    }
                }

			}
			else
			{
				// Ball logic
				sf::Vector2f velocity = aiComponent->getVelocity();

				// Initialize the entity's velocity randomly if it's (0, 0)
				if (velocity == sf::Vector2f(0.0f, 0.0f))
				{
					std::srand(static_cast<unsigned>(std::time(nullptr)));
					velocity.x = (std::rand() % 2 == 0 ? -1.0f : 1.0f) * 200.0f; // Random direction
					velocity.y = (std::rand() % 2 == 0 ? -1.0f : 1.0f) * 200.0f;
					aiComponent->setVelocity(velocity);
				}

				// Move the entity
				transformComponent->position += velocity * deltaTime;

				float width = spriteComponent->sprite.getGlobalBounds().width;
				float height = spriteComponent->sprite.getGlobalBounds().height;

				// Check for collisions with window boundaries
				sf::FloatRect bounds(transformComponent->position.x, transformComponent->position.y, width, height);
				if (bounds.left < 0 || bounds.left + bounds.width > window.getSize().x)
				{
					velocity.x = -velocity.x;
				}
				if (bounds.top < 0 || bounds.top + bounds.height > window.getSize().y)
				{
					velocity.y = -velocity.y;
				}

				aiComponent->setVelocity(velocity);
			}
		}
	}
}
