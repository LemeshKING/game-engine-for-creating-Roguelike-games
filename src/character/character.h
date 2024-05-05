#pragma once
#include"../Health/health.h"
#include"../AnimationManager/AnimationManager.h"


class Character
{
 public:
   std::map<std::string, bool> key;
   ar::AnimationManager animation;
 


   Character();
   virtual void update(const float time, std::vector<std::vector<int>> &location);
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
   virtual void CollisionX(std::vector<std::vector<int>>& location);
   virtual void CollisionY(std::vector<std::vector<int>>& location);
 protected: 
   enum State{ stay, walk, jumping, attack } CharacterState;
   hlth::Health health;
   sf::Texture texture;
   bool alive = true;
   int direction = 1;
   int characterHeight = 0;
   int characterWidth = 0;
   sf::FloatRect rect;
   sf::Sprite sprite;
   float dx = 0;
   float dy = 0;
   bool onGround = false;
   sf::RectangleShape rectangle;
   void Kill();
   virtual void ChangeStateCharacter();
};