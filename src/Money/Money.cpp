#include "Money.h"

Money::Money(int _cost, float _x, float _y)
{
   x = _x;
   y = _y;
   if(!texture.loadFromFile("../src/Money/Coin.png"))
      texture.loadFromFile("../../src/Money/Coin.png");
   cost = _cost;
   sprite.setTexture(texture);
   sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
   sprite.setPosition(_x, _y);
   physicalQ.rect = sprite.getGlobalBounds();

}

void Money::PlayerInteraction(Player& _player)
{
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
   {
      _player.gainMoney(cost);
      sprite.setColor(sf::Color::Black);
   }
}



unsigned int Money::getCost()
{
   return cost;
}
