#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <thread>
#include <chrono>

class Ball
{
private:
    sf::CircleShape ball;
    sf::Vector2f velocity;
    float speed;
    int tmp = 1;

public:
    
    Ball();
    virtual ~Ball();

    
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f& getVelocity() const;
    float getSpeed() const;
    float getRadius() const;

    
    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    void setSpeed(float speed);
    void reverseVelocityX();
    void reverseVelocityY();

    
    void update(sf::RenderWindow& window);
    void render(sf::RenderTarget& target);
    void reset(sf::RenderWindow& window);
};