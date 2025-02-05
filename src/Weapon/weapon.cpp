#include "weapon.h"

void weapon::setRect(sf::FloatRect &_rect)
{
   physicalQ.rect = _rect;
   sprite.setPosition(physicalQ.rect.left, physicalQ.rect.top);
}

void weapon::setRectangle(sf::RectangleShape& _rect)
{
   rectangle = _rect;
}

void weapon::setSrite(sf::Sprite _sprite)
{
   sprite = _sprite;
}

sf::Sprite weapon::getSprite()
{
   return sprite;
}

sf::FloatRect weapon::getRect()
{
    return physicalQ.rect;
}

sf::RectangleShape weapon::getRectangle()
{
   return rectangle;
}

void weapon::update(int x, int y)
{
   physicalQ.rect.left = x - 2;
   physicalQ.rect.top = y + 11.35;
   physicalQ.dy = 0;
   sprite.setPosition(physicalQ.rect.left, physicalQ.rect.top);
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
   sprite.setRotation(angel);
}

void weapon::update()
{
   sprite.setPosition(physicalQ.rect.getPosition());
}
