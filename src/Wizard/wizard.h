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

   void update(const float time, IntVectorVector& location) override;
   void Initialization(int x, int y) override;
   void Attack() override;
private:
   sf::Vector2i directionAtack;
};