#pragma once
#include"../character/character.h"
#include "../Camera/Camera.h"
#include "../Weapon/weapon.h"
#include "../ISubject/ISubject.h"
#include <list>

typedef std::shared_ptr<weapon> SPtrWeapon;
typedef std::list<SPtrObserver> ListUptrObserver;

class Player : public Character, public ISubject
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
   void Attach(SPtrObserver &observer) override;
   void Detach(SPtrObserver &observer) override;
   void Notify() override;
   void gainMoney(unsigned int &cost);

protected:
   void ChangeStateCharacter() override;
   void CollisionX(IntVectorVector& location) override;
   void CollisionY(IntVectorVector& location) override;
private:
   ListUptrObserver Observers;
   SPtrWeapon Weapon;
   bool immunity = false;
   unsigned int wallet = 0;
   Camera camera;
   
};