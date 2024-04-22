#pragma once
#include "../GameObject/GameObject.h"


class Tile
{
private:
   sf::RectangleShape sprite;

   int x = 0, y = 0;
   int tileWidth;
   int tileHeight;
   int tileType;
public:
   GameObject *Object;
   weapon* Weapon;
   sf::RectangleShape getSprite();
   void setSprite(sf::RectangleShape _sprite);
   int getX();
   int getY();
   void setX(int _x);
   void setY(int _y);
   void setType(int _tileType);
   int getTileType();

};