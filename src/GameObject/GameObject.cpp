#include "GameObject.h"

void GameObject::PlayerInteraction(Player& _player)
{

}

void GameObject::setSprite(sf::RectangleShape _sprite)
{
   sprite = _sprite;
   x = _sprite.getPosition().x;
   y = _sprite.getPosition().y;
   SizeX = _sprite.getSize().x;
   SizeY = _sprite.getSize().y;
}

sf::RectangleShape GameObject::getSprite()
{
   return sprite;
}

void GameObject::setX(int _x)
{
   x = _x;
}

void GameObject::setY(int _y)
{
   y = _y;
}

int GameObject::getX()
{
   return x;
}

int GameObject::getY()
{
   return y;
}
