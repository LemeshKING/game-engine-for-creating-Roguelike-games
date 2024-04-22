#pragma once
#include "../GameObject/GameObject.h"

class Teleport : public GameObject
{
   int TeleportationX;
   int TeleportationY;
public:
   Teleport(int _x, int _y);
   void PlayerInteraction(Player& _player) override;
};