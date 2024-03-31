#pragma once
#include"../character/character.h"
#include "../Camera/Camera.h"
#include "../Weapon/weapon.h"

class Player : public Character
{
 public: 

   Player();
   void Initialization(int x, int y);
   void update(const float& time, const std::vector<std::vector<int>>& location) override;
   void setCamera(Camera &_camera);
   Camera getCamera();
   void TakeDamage(int damageValue) override;
   bool isImmunity();
   void removeImmunity();
   void setWeapon(weapon *_weapon);
   weapon* getWeapon();
private:
   weapon *Weapon;
   bool immunity = false;
   Camera camera;
   void CollisionX(const std::vector<std::vector<int>>& location) override;
   void CollisionY(const std::vector<std::vector<int>>& location) override;
};