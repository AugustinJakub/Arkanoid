#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    bool hovered;

public:
    Button() = default;
    Button(const sf::Font& font, const std::string& label,
        const sf::Vector2f& position, const sf::Vector2f& size);

    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
    bool isHovered() const;
    void setPosition(const sf::Vector2f& position);
};