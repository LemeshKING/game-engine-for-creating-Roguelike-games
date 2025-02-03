#pragma once
#include"../character/character.h"
#include"../ProjectTile/ProjectTile.h"

class Enemy : public Character
{
protected: 
   int damageValue = 0;
   float distance = 0;
   sf::FloatRect Vision;
   sf::FloatRect playerPosition;
   int chardgeAttack = 0;
   int attackCooldown = 77;
   int AttackRange = 33;
   bool attacking = false;
   bool sawPlayer = false;
   void Enemy::CollisionX(IntVectorVector& location) override;
   void Enemy::CollisionY(IntVectorVector& location) override;
   bool playerAlive = true;
   unsigned int cost;
   
 public:
   int positionX = 0;
   int positionY = 0;
   virtual void Attack();
   ProjectTile projectTile;
   void SawPlayer(bool _sawPlayer);
   virtual void Initialization(int x, int y);
   void update(const float time, IntVectorVector& location) override;
   void TakeDamage(int damageValue) override;
   void setDamageValue(int _damage);
   int getDamageValue();
   sf::FloatRect getVision();
   void setPlayerPosition(sf::FloatRect _PlayerPosition);
   bool wasAttaking = false;
   unsigned int getCost();
};