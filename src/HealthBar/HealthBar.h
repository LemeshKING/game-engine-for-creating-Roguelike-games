#pragma once
#include<SFML/Graphics.hpp>
#include "../Observer/Observer.h"

class HealthBar : public Observer
{
private:
   sf::RectangleShape fullBar;
   sf::RectangleShape currentHealthBar;
   sf::Font font;
   sf::Text helathPoints;
   int x = 0;
   int y = 0;
   unsigned int maxHp = 0;
 public:
   void update();
   void Initialization(unsigned int _maxHP, int x, int y);
   void setX(int _x);
   void setY(int _y);
   void HealthChange(const unsigned int& _currentHp) override;
   sf::RectangleShape getFullHealthBar();
   sf::RectangleShape getCurrentHealthBar();
   sf::Text getText();
};