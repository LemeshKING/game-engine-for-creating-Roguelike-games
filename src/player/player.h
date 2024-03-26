#pragma once
#include"../character/character.h"
#include "../Camera/Camera.h"

class Player : public Character
{
 public: 
   Camera camera;
   Player();
   Player(int x, int y)
   {
      rect = sf::FloatRect(x,y,40,50);
      rectangle.setSize(sf::Vector2f(rect.width, rect.height));
   }
   void Initialization(int x, int y);
   void update(const float& time, const std::vector<std::vector<int>>& location) override;
private:
   void CollisionX(const std::vector<std::vector<int>>& location) override;
   void CollisionY(const std::vector<std::vector<int>>& location) override;
};