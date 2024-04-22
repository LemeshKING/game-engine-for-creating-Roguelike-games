#include "thorns.h"


void Thorns::PlayerInteraction(Player& _player)
{
   if(!_player.isImmunity())
      _player.TakeDamage(10);
}
