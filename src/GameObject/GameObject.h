#pragma once
#include "SFML/Graphics.hpp"
#include "../player/player.h"

class GameObject
{

protected:
   sf::Texture texture;
   sf::Sprite sprite;
   int x = 0;
   int y = 0;
   int SizeX;
   int SizeY;
public:
   void update();
   PhysicalQuantities physicalQ;
   virtual void PlayerInteraction(Player& _player) = 0;
   void setSprite(sf::Sprite _sprite);
   sf::Sprite getSprite();
   void setX(int _x);
   void setY(int _y);
   int getX();
   int getY();
   void setRect(sf::FloatRect rect);
};