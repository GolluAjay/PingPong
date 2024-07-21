#pragma once
#include <SFML/Graphics.hpp>
#include "ECS/Entity.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/AISystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void handleKeyEvent(sf::Keyboard::Key key, bool isPressed);
    void render();
    void resizeBackground();

    sf::RenderWindow mWindow;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::shared_ptr<Entity> player;
    std::shared_ptr<Entity> ball;
    std::shared_ptr<Entity> opponentPaddle;

    RenderSystem renderSystem;
    InputSystem inputSystem;
    AISystem aiSystem;
    CollisionSystem collisionSystem;
};
