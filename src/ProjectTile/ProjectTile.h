#pragma once
#include <SFML/Graphics.hpp>

class ProjectTile
{
 private:

   sf::FloatRect hitBox;
   sf::RectangleShape rectangle;
   sf::Vector2i direction;
   float distance = 0;
   bool alive = false;
 public:
   float dx = 0.25;
   float dy = 0.15;
   float angel = 0;
   int damageValue = 30;
   ProjectTile();
   void setSprite(sf::RectangleShape _rectangle);
   sf::RectangleShape getSprite();
   sf::FloatRect getRect();
   void setHitBox(sf::FloatRect _HitBox);
   void update(const float time);
   void Initialization(int x, int y);
   void setDirection(sf::Vector2i _direction);
   bool isAlive();
};