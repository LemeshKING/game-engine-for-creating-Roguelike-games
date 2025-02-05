#pragma once
#include "../Health/health.h"
#include "../AnimationManager/AnimationManager.h"
#include "../physicalQuantities/PhysicalQuantities.h"

typedef std::vector<int> IntVector;
typedef std::vector<IntVector> IntVectorVector;

class Character
{
 public:
   std::map<std::string, bool> key;
   ar::AnimationManager animation;
   PhysicalQuantities physicalQ;


   Character();
   virtual void update(const float time, IntVectorVector &location);
   void setDirection(int _direction);
   void setDx(float _dx);
   void setDy(float _dy);
   void setCharacterHeight(int _CharacterHeight);
   void setCharacterWidth(int _CharacterWidth);
   bool isOnGround();
   sf::RectangleShape getRectangle();
   hlth::Health getHealth();
   void setHealth(hlth::Health _Health);
   sf::FloatRect getRect();
   virtual void TakeDamage(int damageValue);
   bool isAlive();
   void setRect(sf::FloatRect _rect);
   void jump();
   void stateOnGround();
   void setLeft(float left);
   void setTop(float top);
   float getDx();
   float getDy();
   int getDirection();
 private:
   
 protected: 
   enum State{ stay, walk, jumping, attack } CharacterState;
   hlth::Health health;
   sf::Texture texture;
   bool alive = true;
   int direction = 1;
   int characterHeight = 0;
   int characterWidth = 0;
   sf::Sprite sprite;
   bool onGround = false;
   sf::RectangleShape rectangle;
   void Kill();
   virtual void ChangeStateCharacter();
   virtual void CollisionX(IntVectorVector& location);
   virtual void CollisionY(IntVectorVector& location);
};