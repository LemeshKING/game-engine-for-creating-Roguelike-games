#include "MoneyUI.h"

void MoneyUI::update()
{
   sprite.setPosition(x + 420, y + 6.9 * 32);
   countOfMoney.setPosition(x + 440, y + 6.9 * 32);
}

void MoneyUI::Initialization(int& _x, int& _y)
{
   x = _x; 
   y = _y;
   if (!font.loadFromFile("../src/arial/ttt.otf"))
      font.loadFromFile("../../src/arial/ttt.otf");

   countOfMoney.setFont(font);
   countOfMoney.setCharacterSize(12);
   countOfMoney.setOutlineThickness(0.5);
   countOfMoney.setFillColor(sf::Color::Black);
   countOfMoney.setString("0");

   if (!texture.loadFromFile("../src/Money/Coin.png"))
      texture.loadFromFile("../../src/Money/Coin.png");
   sprite.setTexture(texture);
   sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
   sprite.setPosition(x, y);
   countOfMoney.setPosition(x + 20, y);
}

void MoneyUI::setX(int _x)
{
   x = _x;
}

void MoneyUI::setY(int _y)
{
   y = _y;
}

void MoneyUI::HealthChange(const unsigned int& _currentHp)
{
}

void MoneyUI::MoneyChange(const unsigned int& _currentMoney)
{
   countOfMoney.setString(std::to_string(_currentMoney));
}

sf::Sprite MoneyUI::getSprite()
{
    return sprite;
}

sf::Text MoneyUI::getText()
{
   return countOfMoney;
}
