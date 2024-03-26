#pragma once
#include"../Health/health.h"
#include"../AnimationManager/AnimationManager.h"


class Character
{
 public:
   hlth::Health health;
   ar::AnimationManager Animation;
   sf::FloatRect rect;
   sf::Sprite sprite;
   float dx = 0;
   float dy = 0;
   bool onGround = false;
   sf::RectangleShape rectangle;
   Character();
   virtual void update(const float &time, const std::vector<std::vector<int>> &location);
   
 private:
   virtual void CollisionX(const std::vector<std::vector<int>>& location);
   virtual void CollisionY(const std::vector<std::vector<int>>& location);
};