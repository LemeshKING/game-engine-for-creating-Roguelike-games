#pragma once
#include <SFML/Graphics.hpp>
#include "../physicalQuantities/PhysicalQuantities.h"
class weapon
{
 public:
   PhysicalQuantities physicalQ;
   void setRect(sf::FloatRect &_rect);
   void setRectangle(sf::RectangleShape &_rect);
   void setSrite(sf::Sprite _sprite);
   sf::Sprite getSprite();
   sf::FloatRect getRect();
   sf::RectangleShape getRectangle();
   void update(int x, int y);
   void setDamageValue(unsigned int _damageValue);
   unsigned int getDamageValue();
   void setRotation(float angel);
   void update();
 protected:
   sf::Texture texture;
   unsigned int damageValue;
   sf::FloatRect rect;
   sf::RectangleShape rectangle;
   sf::Sprite sprite;
   virtual void Attack() = 0;

};