#pragma once
#include"../Health/health.h"
#include"../AnimationManager/AnimationManager.h"
#include"SFML/Graphics.hpp"

class Character
{
 public:
   hlth::Health health;
   ar::AnimationManager Animation;
   sf::FloatRect rect;
   Character();
   void update(int time);
 private:
   virtual void CollisionX();
   virtual void CollisionY();
};