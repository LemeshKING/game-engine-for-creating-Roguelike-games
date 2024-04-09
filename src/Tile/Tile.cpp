#include "Tile.h"

sf::RectangleShape Tile::getSprite()
{
   return sprite;
}

void Tile::setSprite(sf::RectangleShape _sprite)
{
   sprite = _sprite;
   x = _sprite.getPosition().x;
   y = _sprite.getPosition().y;
   tileWidth = _sprite.getSize().x;
   tileHeight = _sprite.getSize().y;
}

int Tile::getX()
{
   return x;
}

int Tile::getY()
{
   return y;
}

void Tile::setX(int _x)
{
   x = _x;
}

void Tile::setY(int _y)
{
   y = _y;
}

void Tile::setType(int _tileType)
{
   tileType = _tileType;
}

int Tile::getTileType()
{
   return tileType;
}
