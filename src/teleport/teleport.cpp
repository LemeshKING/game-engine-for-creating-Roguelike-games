#include "teleport.h"

Teleport::Teleport(int _x, int _y)
{
   TeleportationX = _x;
   TeleportationY = _y;
   if (!texture.loadFromFile("../src/teleport/teleport.png"))
      texture.loadFromFile("../../src/teleport/teleport.png");
   sprite.setTexture(texture);
   sprite.setTextureRect(sf::IntRect(0, 0, 32, 96));
   physicalQ.rect = sprite.getGlobalBounds();
   physicalQ.elasticityCoefficient = 0;
}

void Teleport::PlayerInteraction(Player& _player)
{
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
   {
      sf::FloatRect tmp(TeleportationX, TeleportationY, _player.getRect().width, _player.getRect().height);
      _player.setRect(tmp);
   }
}
