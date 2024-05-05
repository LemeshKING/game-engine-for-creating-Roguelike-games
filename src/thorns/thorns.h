#pragma once
#include"../GameObject/GameObject.h"


class Thorns: public GameObject
{
   sf::FloatRect rect;
   
public:
   Thorns();
   void PlayerInteraction(Player& _player) override;
};