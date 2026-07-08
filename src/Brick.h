#pragma once

#include <SFML/Graphics.hpp>

class Brick
{
private:
    sf::RectangleShape brick;
    bool destroyed;
    int points;
    int type;

public:
    
    
    Brick();
    Brick(float x, float y, int type = 0);
    virtual ~Brick();

    
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    bool isDestroyed() const;
    int getPoints() const;
    int getType() const;

   
    void setPosition(float x, float y);
    void setType(int type);
    void destroy();

    
    void render(sf::RenderTarget& target);
};