#include "AIComponent.hpp"

AIComponent::AIComponent(float speed, bool isPaddle)
    : speed(speed), isPaddle(isPaddle), velocity(sf::Vector2f(0.0f, 0.0f))
{
}

void AIComponent::setVelocity(const sf::Vector2f &velocity)
{
    this->velocity = velocity;
}

sf::Vector2f AIComponent::getVelocity() const
{
    return velocity;
}

float AIComponent::getSpeed() const
{
    return speed;
}

bool AIComponent::getIsPaddle() const
{
    return isPaddle;
}
