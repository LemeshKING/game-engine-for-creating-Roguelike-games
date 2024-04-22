#pragma once
#include "SFML/Graphics.hpp"
#include "../player/player.h"

class GameObject
{
   int x = 0;
   int y = 0;
   int SizeX;
   int SizeY;
protected:
   sf::RectangleShape sprite;
public:
   virtual void PlayerInteraction(Player& _player);
   void setSprite(sf::RectangleShape _sprite);
   sf::RectangleShape getSprite();
   void setX(int _x);
   void setY(int _y);
   int getX();
   int getY();
};