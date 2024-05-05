#include "HealthBar.h"

void HealthBar::update(const unsigned int& _currentHp)
{
   fullBar.setPosition(x - fullBar.getSize().x + 32, y + 7 * 32);
   currentHealthBar.setSize(sf::Vector2f((_currentHp * 5 / fullBar.getSize().x) * fullBar.getSize().x, 16));
   currentHealthBar.setPosition(x - fullBar.getSize().x + 32, y + 7 * 32);
}

void HealthBar::Initialization(unsigned int _maxHP,int x, int y)
{
   fullBar.setSize(sf::Vector2f(_maxHP * 5, 16));
   fullBar.setFillColor(sf::Color::Color(255,255,255,0));
   fullBar.setOutlineThickness(1);
   fullBar.setOutlineColor(sf::Color::Black);
   fullBar.setPosition(x * 32 + 10, y * 32);
   currentHealthBar.setSize(sf::Vector2f(_maxHP * 5, 16));
   currentHealthBar.setFillColor(sf::Color::Green);
   currentHealthBar.setPosition(x * 32 + 10, y * 32);
}

void HealthBar::setX(int _x)
{
   x =_x;
}

void HealthBar::setY(int _y)
{
   y = _y;
}

sf::RectangleShape HealthBar::getFullHealthBar()
{
   return fullBar;
}

sf::RectangleShape HealthBar::getCurrentHealthBar()
{
   return currentHealthBar;
}


