#pragma once
#include<SFML/Graphics.hpp>

class HealthBar
{
private:
   sf::RectangleShape fullBar;
   sf::RectangleShape currentHealthBar;
   int x = 0;
   int y = 0;
 public:
   void update(const unsigned int &_currentHp);
   void Initialization(unsigned int _maxHP, int x, int y);
   void setX(int _x);
   void setY(int _y);
   sf::RectangleShape getFullHealthBar();
   sf::RectangleShape getCurrentHealthBar();
};