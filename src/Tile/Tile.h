#pragma once
#include "../GameObject/GameObject.h"
#include "../enemy/enemy.h"



typedef std::shared_ptr<GameObject> SPtrGameObject;

class Tile
{
private:
   
   int x = 0, y = 0;
   int tileWidth;
   int tileHeight;
   int tileType;
public:
   sf::Sprite sprite;
   std::vector<std::shared_ptr<Enemy>> enemysOnTile;
   std::vector<SPtrGameObject> objectsOnTile;
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