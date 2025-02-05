#pragma once
#include"../GameObject/GameObject.h"


class Thorns: public GameObject
{
   
public:
   Thorns();
   void PlayerInteraction(Player& _player) override;
};