#include "HealthBar.h"

void HealthBar::update(const unsigned int & _currentHp)
{
   float ration = (float)_currentHp / (float)maxHp;
   fullBar.setPosition(x - fullBar.getSize().x + 32, y + 7 * 32);
   currentHealthBar.setSize(sf::Vector2f(ration * fullBar.getSize().x, 16));
   currentHealthBar.setPosition(x - fullBar.getSize().x + 32, y + 7 * 32);
   helathPoints.setString(std::to_string(_currentHp));
   helathPoints.setPosition(x - fullBar.getSize().x + 282, y + 7 * 32);
}

void HealthBar::Initialization(unsigned int _maxHP,int x, int y)
{
   maxHp = _maxHP;                     
   font.loadFromFile("../src/arial/ttt.otf");
   helathPoints.setFont(font);
   helathPoints.setCharacterSize(12);
   helathPoints.setOutlineThickness(0.5);
   helathPoints.setFillColor(sf::Color::Black);
   helathPoints.setString(std::to_string(_maxHP));
   helathPoints.setPosition(x * 32 + 250, y * 32);

   fullBar.setSize(sf::Vector2f(500, 16));
   fullBar.setFillColor(sf::Color::Color(255,255,255,0));
   fullBar.setOutlineThickness(1);
   fullBar.setOutlineColor(sf::Color::Black);
   fullBar.setPosition(x * 32 + 10, y * 32);
   currentHealthBar.setSize(sf::Vector2f(500, 16));
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

sf::Text HealthBar::getText()
{
   return helathPoints;
}


