#pragma once

#include"../GameObject/GameObject.h"
#include<SFML/Graphics.hpp>

class Money : public GameObject
{
   unsigned int cost;
public:
   Money(){};
   Money(int _cost, float _x, float _y);
   void PlayerInteraction(Player & _player) override;
   unsigned int getCost();

};