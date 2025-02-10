#pragma once
#include "SFML/Graphics.hpp"
#include "../Observer/Observer.h"

class MoneyUI : public Observer
{
 private:
   sf::Sprite sprite;
   sf::Font font;
   sf::Text countOfMoney;
   sf::Texture texture;
   int x = 0;
   int y = 0;
 public:
   void update();
   void Initialization(int &_x, int &_y);
   void setX(int _x);
   void setY(int _y);
   void HealthChange(const unsigned int& _currentHp) override;
   void MoneyChange(const unsigned int& _currentMoney) override;
   sf::Sprite getSprite();
   sf::Text getText();
   
};