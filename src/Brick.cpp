#include "Brick.h"

Brick::Brick()
{
    this->destroyed = false;
    this->type = 0;
    this->points = 10;

    this->brick.setSize(sf::Vector2f(75.f, 30.f));
    this->brick.setFillColor(sf::Color::Red);
 
   
}



Brick::Brick(float x, float y, int type)
{
    this->destroyed = false;
    this->type = type;

    this->brick.setSize(sf::Vector2f(75.f, 30.f));
    this->brick.setPosition(x, y);
    

    
    switch (type)
    {
    case 0:
        this->brick.setFillColor(sf::Color::Red);
        this->points = 10;
        break;
    case 1:
        this->brick.setFillColor(sf::Color::Magenta);
        this->points = 15;
        break;
    case 2:
        this->brick.setFillColor(sf::Color::Green);
        this->points = 20;
        break;
    case 3:
        this->brick.setFillColor(sf::Color::Cyan);
        this->points = 25;
        break;
    case 4:
        this->brick.setFillColor(sf::Color::Blue);
        this->points = 30;
        break;
    default:
        this->brick.setFillColor(sf::Color::Magenta);
        this->points = 10;
        break;
    }
}

Brick::~Brick()
{
}


const sf::Vector2f& Brick::getPosition() const
{
    return this->brick.getPosition();
}

const sf::FloatRect Brick::getGlobalBounds() const
{
    return this->brick.getGlobalBounds();
}

bool Brick::isDestroyed() const
{
    return this->destroyed;
}

int Brick::getPoints() const
{
    return this->points;
}

int Brick::getType() const
{
    return this->type;
}


void Brick::setPosition(float x, float y)
{
    this->brick.setPosition(x, y);
}

void Brick::setType(int type)
{
    this->type = type;
    
    switch (type)
    {
    case 0:
        this->brick.setFillColor(sf::Color::Red);
        this->points = 10;
        break;
    case 1:
        this->brick.setFillColor(sf::Color::Green);
        this->points = 15;
        break;
    case 2:
        this->brick.setFillColor(sf::Color::Blue);
        this->points = 20;
        break;
    case 3:
        this->brick.setFillColor(sf::Color::Yellow);
        this->points = 25;
        break;
    case 4:
        this->brick.setFillColor(sf::Color::Magenta);
        this->points = 30;
        break;
    }
}

void Brick::destroy()
{
    this->destroyed = true;
}


void Brick::render(sf::RenderTarget& target)
{
    if (!this->destroyed)
    {
        target.draw(this->brick);
    }
}