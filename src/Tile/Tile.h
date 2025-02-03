#pragma once
#include "../GameObject/GameObject.h"



typedef std::shared_ptr<GameObject> SPtrGameObject;

class Tile
{
private:
   sf::Sprite sprite;
   int x = 0, y = 0;
   int tileWidth;
   int tileHeight;
   int tileType;
public:
   SPtrGameObject Object;
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