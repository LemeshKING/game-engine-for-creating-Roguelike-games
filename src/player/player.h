#pragma once
#include"../character/character.h"
#include "../Camera/Camera.h"

class Player : public Character
{
 public: 

   Player();
   void Initialization(int x, int y);
   void update(const float& time, const std::vector<std::vector<int>>& location) override;
   void setCamera(Camera _camera);
   Camera getCamera();
private:
   Camera camera;
   void CollisionX(const std::vector<std::vector<int>>& location) override;
   void CollisionY(const std::vector<std::vector<int>>& location) override;
};