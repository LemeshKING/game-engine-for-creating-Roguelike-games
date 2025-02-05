#include "thorns.h"


Thorns::Thorns()
{
   if (!texture.loadFromFile("../src/thorns/thorn.png"))
      texture.loadFromFile("../../src/thorns/thorn.png");
   sprite.setTexture(texture);
   sprite.setTextureRect(sf::IntRect(0,0,32,36));
   physicalQ.rect = sprite.getGlobalBounds();
}

void Thorns::PlayerInteraction(Player& _player)
{
   _player.TakeDamage(10);
}
