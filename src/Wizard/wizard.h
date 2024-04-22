#pragma once
#include"../enemy/enemy.h"


class Wizard : public Enemy
{
public:
   Wizard()
   {
      AttackRange = 200;
      attackCooldown = 70;
   }
   sf::Vector2i directionAtack;
   void update(const float time, std::vector<std::vector<int>>& location) override;
   void Initialization(int x, int y);
   void Attack() override;
};