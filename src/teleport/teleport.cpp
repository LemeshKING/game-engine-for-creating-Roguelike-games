#include "teleport.h"

Teleport::Teleport(int _x, int _y)
{
   TeleportationX = _x;
   TeleportationY = _y;
}

void Teleport::PlayerInteraction(Player& _player)
{
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
   {
      sf::FloatRect tmp(TeleportationX, TeleportationY, _player.getRect().width, _player.getRect().height);
      _player.setRect(tmp);
   }
}
