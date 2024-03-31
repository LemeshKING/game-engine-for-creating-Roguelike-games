#pragma once
#include"../character/character.h"

class Enemy : public Character
{
private: 
   int damageValue;
   float distance;
   void Enemy::CollisionX(const std::vector<std::vector<int>>& location) override;
   void Enemy::CollisionY(const std::vector<std::vector<int>>& location) override;
 public:
   void Initialization(int x, int y);
   void update(const float& time, const std::vector<std::vector<int>>& location) override;
   void setDamageValue(int _damage);
   int getDamageValue();
};