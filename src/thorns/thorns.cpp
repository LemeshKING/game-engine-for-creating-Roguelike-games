#include "thorns.h"


Thorns::Thorns()
{
   if (!texture.loadFromFile("../src/thorns/thorn.png"))
      texture.loadFromFile("../../src/thorns/thorn.png");
   sprite.setTexture(texture);
   sprite.setTextureRect(sf::IntRect(0,0,32,36));
   
}

void Thorns::PlayerInteraction(Player& _player)
{
   if(!_player.isImmunity())
      _player.TakeDamage(10);
}
