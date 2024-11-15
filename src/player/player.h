#pragma once
#include"../character/character.h"
#include "../Camera/Camera.h"
#include "../Weapon/weapon.h"

typedef std::shared_ptr<weapon> SPtrWeapon;

class Player : public Character
{
 public: 

   Player();
   void Initialization(int x, int y);
   void update(const float time, IntVectorVector& location) override;
   void setCamera(Camera &_camera);
   Camera getCamera();
   void TakeDamage(int damageValue) override;
   bool isImmunity();
   void removeImmunity();
   void setWeapon(SPtrWeapon &_weapon);
   void BecomeImmune();
   SPtrWeapon getWeapon();
   bool satDown = false;
   bool dashing = false;
   int dashFramers = 0;
   int dashColdown = 77;
   bool canMove = true;
   int immuneFrames = 0;
protected:
   void ChangeStateCharacter() override;
private:
 
   SPtrWeapon Weapon;
   bool immunity = false;

   Camera camera;
   void CollisionX(IntVectorVector& location) override;
   void CollisionY(IntVectorVector& location) override;
};