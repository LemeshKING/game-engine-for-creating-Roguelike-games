#pragma once
#include <SFML/Graphics.hpp>

class weapon
{
 public:
   void setRect(sf::FloatRect &_rect);
   void setRectangle(sf::RectangleShape &_rect);
   sf::FloatRect getRect();
   sf::RectangleShape getRectangle();
   void update(int x, int y);
   void setDamageValue(unsigned int _damageValue);
   unsigned int getDamageValue();
 protected:
   unsigned int damageValue;
   sf::FloatRect rect;
   sf::RectangleShape rectangle;
   virtual void Attack() = 0;

};