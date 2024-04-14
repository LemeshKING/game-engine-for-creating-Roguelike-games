#pragma once
#include"../character/character.h"

class Enemy : public Character
{
private: 
   int damageValue;
   float distance;
   sf::FloatRect Vision;
   sf::FloatRect playerPosition;
   int chardgeAttack = 0;
   int attackCooldown = 77;
   int AttackRange = 33;
   bool attacking = false;
   bool sawPlayer = false;
   void Enemy::CollisionX( std::vector<std::vector<Tile>>& location) override;
   void Enemy::CollisionY( std::vector<std::vector<Tile>>& location) override;
   void Attack();
   
 public:
  
   void SawPlayer();
   void Initialization(int x, int y);
   void update(const float time, std::vector<std::vector<Tile>>& location) override;
   void TakeDamage(int damageValue) override;
   void setDamageValue(int _damage);
   int getDamageValue();
   sf::FloatRect getVision();
   void setPlayerPosition(sf::FloatRect _PlayerPosition);
};