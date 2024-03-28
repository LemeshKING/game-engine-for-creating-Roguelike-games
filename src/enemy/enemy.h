#pragma once
#include"../character/character.h"

class Enemy : public Character
{
private: 
   float distance;
   void Enemy::CollisionX(const std::vector<std::vector<int>>& location);
   void Enemy::CollisionY(const std::vector<std::vector<int>>& location);
 public:
   void Initialization(int x, int y);
   void update(const float& time, const std::vector<std::vector<int>>& location) override;
};