#pragma once
#include"../character/character.h"

class Enemy : public Character
{
private: 
   int damageValue;
   float distance;
   sf::FloatRect Vision;
   sf::FloatRect playerPosition;

   bool sawPlayer = false;
   void Enemy::CollisionX( std::vector<std::vector<Tile>>& location) override;
   void Enemy::CollisionY( std::vector<std::vector<Tile>>& location) override;
 public:
    sf::RectangleShape visionRect;
   void SawPlayer();
   void Initialization(int x, int y);
   void update(const float time, std::vector<std::vector<Tile>>& location) override;
   void setDamageValue(int _damage);
   int getDamageValue();
   sf::FloatRect getVision();
   void setPlayerPosition(sf::FloatRect _PlayerPosition);
};