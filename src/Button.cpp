#include "Button.h"

Button::Button(const sf::Font& font, const std::string& label,
    const sf::Vector2f& position, const sf::Vector2f& size)
    : hovered(false) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color(100, 100, 100));

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(
        position.x + size.x / 2 - text.getGlobalBounds().width / 2,
        position.y + size.y / 2 - text.getGlobalBounds().height / 2 - 5
    );
}

void Button::update(const sf::Vector2f& mousePos) {
    hovered = shape.getGlobalBounds().contains(mousePos);
    shape.setFillColor(hovered ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    shape.setOutlineColor(hovered ? sf::Color::White : sf::Color(100, 100, 100));
}

void Button::render(sf::RenderTarget& target) {
    target.draw(shape);
    target.draw(text);
}

bool Button::isHovered() const {
    return hovered;
}

void Button::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
    text.setPosition(
        position.x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2,
        position.y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2 - 5
    );
}