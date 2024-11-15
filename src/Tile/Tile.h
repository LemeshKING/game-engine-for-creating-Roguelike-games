#pragma once
#include "../GameObject/GameObject.h"

class Tile
{
private:
   sf::Sprite sprite;

   int x = 0, y = 0;
   int tileWidth;
   int tileHeight;
   int tileType;
public:
   GameObject *Object;
   SPtrWeapon Weapon;
   sf::Sprite getSprite();
   void setSprite(sf::Sprite _sprite);
   int getX();
   int getY();
   void setX(int _x);
   void setY(int _y);
   void setType(int _tileType);
   int getTileType();

};