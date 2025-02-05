#include "GameObject.h"

void GameObject::update()
{
   sprite.setPosition(physicalQ.rect.getPosition());
}

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
   physicalQ.rect.left = x = _x;
   sprite.setPosition(x, y);

}

void GameObject::setY(int _y)
{
   physicalQ.rect.top = y = _y;
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

void GameObject::setRect(sf::FloatRect rect)
{
   physicalQ.rect = rect;
}
