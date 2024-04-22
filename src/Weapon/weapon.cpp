#include "weapon.h"

void weapon::setRect(sf::FloatRect &_rect)
{
   rect = _rect;
}

void weapon::setRectangle(sf::RectangleShape& _rect)
{
   rectangle = _rect;
}

sf::FloatRect weapon::getRect()
{
    return rect;
}

sf::RectangleShape weapon::getRectangle()
{
   return rectangle;
}

void weapon::update(int x, int y)
{
   rect.left = x;
   rect.top = y + 10;
   rectangle.setPosition(rect.left, rect.top);
}

void weapon::setDamageValue(unsigned int _damageValue)
{
   damageValue = _damageValue;
}

unsigned int weapon::getDamageValue()
{
   return damageValue;
}

void weapon::setRotation(float angel)
{
   rectangle.setRotation(angel);
}
