#include "Ball.h"

Ball::Ball() {
    this->speed = 5.f;
    this->velocity = sf::Vector2f(0.8f, -0.8f);

    this->ball.setRadius(10.f);
    this->ball.setFillColor(sf::Color::Yellow);
    this->ball.setPosition(400.f, 300.f);
}

Ball::~Ball() {
}

const sf::Vector2f& Ball::getPosition() const {
    return this->ball.getPosition();
}

const sf::FloatRect Ball::getGlobalBounds() const {
    return this->ball.getGlobalBounds();
}

const sf::Vector2f& Ball::getVelocity() const {
    return this->velocity;
}

float Ball::getSpeed() const {
    return this->speed;
}

float Ball::getRadius() const {
    return this->ball.getRadius();
}

void Ball::setPosition(float x, float y) {
    this->ball.setPosition(x, y);
}

void Ball::setVelocity(float x, float y) {
    this->velocity.x = x;
    this->velocity.y = y;
}

void Ball::setSpeed(float speed) {
    this->speed = speed;
}

void Ball::reverseVelocityX() {
    this->velocity.x = -this->velocity.x;
}

void Ball::reverseVelocityY() {
    this->velocity.y = -this->velocity.y;
}

void Ball::update(sf::RenderWindow& window) {
    this->ball.move(this->velocity.x * this->speed, this->velocity.y * this->speed);

    
    if (this->ball.getPosition().x < 0 ||
        this->ball.getPosition().x + this->ball.getRadius() * 2 > window.getSize().x) {
        this->reverseVelocityX();
    }

    
    if (this->ball.getPosition().y < 0) {
        this->reverseVelocityY();
    }

    
}

void Ball::render(sf::RenderTarget& target) {
    target.draw(this->ball);
}

void Ball::reset(sf::RenderWindow& window) {
   

    this->ball.setPosition(window.getSize().x / 2.f - this->ball.getRadius(),
        window.getSize().y / 2.f - this->ball.getRadius());

    
    
    this->velocity = sf::Vector2f(1.f, -1.f);

    
}