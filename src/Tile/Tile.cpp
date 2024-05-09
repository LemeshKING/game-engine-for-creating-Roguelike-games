#include "Tile.h"

sf::Sprite Tile::getSprite()
{
   return sprite;
}

void Tile::setSprite(sf::Sprite _sprite)
{
   sprite = _sprite;
   x = _sprite.getPosition().x;
   y = _sprite.getPosition().y;
   tileWidth = 32;
   tileHeight = 32;
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
   sprite.setPosition(x,y);
}

void Tile::setY(int _y)
{
   y = _y;
   sprite.setPosition(x, y);
}

void Tile::setType(int _tileType)
{
   tileType = _tileType;
}

int Tile::getTileType()
{
   return tileType;
}


