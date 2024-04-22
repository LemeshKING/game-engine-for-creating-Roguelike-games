#pragma once
#include"../GameObject/GameObject.h"


class Thorns: public GameObject
{
   sf::FloatRect rect;
public:
   void PlayerInteraction(Player& _player) override;
};