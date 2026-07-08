#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape paddle;
    float speed;
public:
    Paddle();
    ~Paddle();

    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    float getSpeed() const;
    sf::Vector2f getSize() const;

    void setPosition(float x, float y);
    void setSpeed(float speed);
    void setSize(float width, float height);

    void update(sf::RenderWindow& window);
    void render(sf::RenderTarget& target);


};