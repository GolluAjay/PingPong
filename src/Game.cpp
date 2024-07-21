#include "Game.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/AIComponent.hpp"
#include <iostream>
#include <filesystem>
#include "utils/Utils.hpp"

Game::Game()
    : mWindow(sf::VideoMode(1440, 810), "PING PONG")
{
    mWindow.setFramerateLimit(60); // Limit the frame rate to 60 FPS

    // Print the current working directory
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

    // Load the background texture
    if (!backgroundTexture.loadFromFile(std::filesystem::current_path().string() + "/assets/images/background.png"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Resize the background to fill the window
    resizeBackground();

    // Create the player entity
    player = std::make_shared<Entity>();
    auto transform = std::make_shared<TransformComponent>();
    auto sprite = std::make_shared<SpriteComponent>(std::filesystem::current_path().string() + "/assets/images/paddle.png");

    // Add a bounding box component to the player
    sf::Vector2f minBounds(static_cast<float>(mWindow.getSize().x / 7.0f - sprite->texture.getSize().x), 0.0f);
    sf::Vector2f maxBounds(static_cast<float>(mWindow.getSize().x / 7.0f), static_cast<float>(mWindow.getSize().y));
    auto boundingBox = std::make_shared<BoundingBoxComponent>(minBounds, maxBounds);
    auto collision = std::make_shared<CollisionComponent>(sf::FloatRect(0.0f, 0.0f, sprite->texture.getSize().x, sprite->texture.getSize().y));

    // Add a input component to the player
    auto inputComponent = std::make_shared<InputComponent>();
    inputComponent->setKey(sf::Keyboard::Up, false);
    inputComponent->setKey(sf::Keyboard::Down, false);
    inputComponent->setKey(sf::Keyboard::Left, false);
    inputComponent->setKey(sf::Keyboard::Right, false);

    player->addComponent(transform);
    player->addComponent(sprite);
    player->addComponent(boundingBox);
    player->addComponent(inputComponent);
    player->addComponent(collision);

    ball = std::make_shared<Entity>();
    auto ballTransform = std::make_shared<TransformComponent>();
    auto ballSprite = std::make_shared<SpriteComponent>(std::filesystem::current_path().string() + "/assets/images/ball.png");
    auto ballCollision = std::make_shared<CollisionComponent>(sf::FloatRect(0.0f, 0.0f, ballSprite->texture.getSize().x, ballSprite->texture.getSize().y));
    auto ballAI = std::make_shared<AIComponent>();

    ball->addComponent(ballTransform);
    ball->addComponent(ballSprite);
    ball->addComponent(ballAI);
    ball->addComponent(ballCollision);
    centerSpriteInWindow(ballSprite, mWindow, ballTransform);

    // Create the opponent AI paddle entity
    opponentPaddle = std::make_shared<Entity>();
    auto opponentTransform = std::make_shared<TransformComponent>();
    auto opponentSprite = std::make_shared<SpriteComponent>(std::filesystem::current_path().string() + "/assets/images/paddle.png");
    auto opponentComponent = std::make_shared<AIComponent>(200.0f, true);
    auto opponentCollision = std::make_shared<CollisionComponent>(sf::FloatRect(0.0f, 0.0f, sprite->texture.getSize().x, sprite->texture.getSize().y));
    // Add a bounding box component to the opponent AI paddle
    auto opponentBoundingBox = std::make_shared<BoundingBoxComponent>(
        sf::Vector2f(static_cast<float>(mWindow.getSize().x - maxBounds.x), 0.0f),
        sf::Vector2f(static_cast<float>(mWindow.getSize().x - minBounds.x), static_cast<float>(mWindow.getSize().y)));

    opponentPaddle->addComponent(opponentSprite);
    opponentPaddle->addComponent(opponentTransform);
    opponentPaddle->addComponent(opponentBoundingBox);
    opponentPaddle->addComponent(opponentComponent);
    opponentPaddle->addComponent(opponentCollision);
    clampToBounds(opponentSprite, opponentTransform, opponentBoundingBox);

    // Add the entities to the systems
    renderSystem.addEntity(ball);
    renderSystem.addEntity(player);
    renderSystem.addEntity(opponentPaddle);

    inputSystem.addEntity(player);

    aiSystem.addEntity(ball);
    aiSystem.addEntity(opponentPaddle);

    collisionSystem.addEntity(ball);
    collisionSystem.addEntity(player);
    collisionSystem.addEntity(opponentPaddle);
}

void Game::run()
{
    const float timePerFrame = 1.0f / 60.0f; // 60 FPS
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;

        processEvents();

        while (timeSinceLastUpdate.asSeconds() > timePerFrame)
        {
            timeSinceLastUpdate -= sf::seconds(timePerFrame);
            update(sf::seconds(timePerFrame));
        }

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            handleKeyEvent(event.key.code, true);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            handleKeyEvent(event.key.code, false);
        }
    }
}

void Game::handleKeyEvent(sf::Keyboard::Key key, bool isPressed)
{
    auto inputComponent = player->getComponent<InputComponent>();
    if (inputComponent)
    {
        inputComponent->setKey(key, isPressed);
    }
}

void Game::update(sf::Time deltaTime)
{
    inputSystem.update(deltaTime.asSeconds());
    renderSystem.update(deltaTime.asSeconds()); // Only call this if you keep the deltaTime parameter
    aiSystem.update(deltaTime.asSeconds(), mWindow, ball);
    collisionSystem.update(deltaTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();

    // Draw the background first
    mWindow.draw(backgroundSprite);

    // Render the rest of the entities
    renderSystem.render(mWindow);
    mWindow.display();
}

void Game::resizeBackground()
{
    // Get the size of the window
    sf::Vector2u windowSize = mWindow.getSize();

    // Get the size of the texture
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // Calculate scale factors
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Apply the scale to the sprite
    backgroundSprite.setScale(scaleX, scaleY);
}

// https://www.mariowiki.com/Gallery:Mario_sprites_and_models