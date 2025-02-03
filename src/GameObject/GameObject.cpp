#include "GameObject.h"

void GameObject::setSprite(sf::Sprite _sprite)
{
   sprite = _sprite;
}

sf::Sprite GameObject::getSprite()
{
   return sprite;
}

void GameObject::setX(int _x)
{
   x = _x;
   sprite.setPosition(x, y);
}

void GameObject::setY(int _y)
{
   y = _y;
   sprite.setPosition(x, y);
}

int GameObject::getX()
{
   return x;
}

int GameObject::getY()
{
   return y;
}
