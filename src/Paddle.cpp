#include "Paddle.h"

Paddle::Paddle() {
    speed = 8.f;
    paddle.setSize(sf::Vector2f(120.f, 25.f));
    paddle.setFillColor(sf::Color::White);
    paddle.setPosition(400.f, 550.f);
}

Paddle::~Paddle() {
}

const sf::Vector2f& Paddle::getPosition() const {
    return paddle.getPosition();
}

const sf::FloatRect Paddle::getGlobalBounds() const {
    return paddle.getGlobalBounds();
}

float Paddle::getSpeed() const {
    return speed;
}

sf::Vector2f Paddle::getSize() const {
    return paddle.getSize();
}

void Paddle::setPosition(float x, float y) {
    paddle.setPosition(x, y);
}

void Paddle::setSpeed(float speed) {
    this->speed = speed;
}

void Paddle::setSize(float width, float height) {
    paddle.setSize(sf::Vector2f(width, height));
}

void Paddle::update(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (paddle.getPosition().x > 0)
            paddle.move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (paddle.getPosition().x + paddle.getSize().x < window.getSize().x)
            paddle.move(speed, 0.f);
    }
}

void Paddle::render(sf::RenderTarget& target) {
    target.draw(paddle);
}