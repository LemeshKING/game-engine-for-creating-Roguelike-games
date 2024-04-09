#include "enemy.h"

void Enemy::SawPlayer()
{
   sawPlayer = true;
}

void Enemy::Initialization(int x, int y)
{
   rectangle.setFillColor(sf::Color::Red);
   rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   Vision = sf::FloatRect(x + characterWidth, y - characterHeight, 200, 200);
   rectangle.setSize(sf::Vector2f(rect.width,rect.height));
   rectangle.setPosition(sf::Vector2f(rect.left,rect.top));
   visionRect.setSize(sf::Vector2f(Vision.width, Vision.height));
   visionRect.setPosition(sf::Vector2f(Vision.left, Vision.top));
   visionRect.setFillColor(sf::Color::Yellow);
   dx = 0.15;
}

void Enemy::update(const float time, std::vector<std::vector<Tile>>& location)
{
   dx = 0.15 * direction;
   if(Vision.intersects(playerPosition) && !sawPlayer)
      sawPlayer = true;
   if(!sawPlayer)
   {  
      if(abs(distance) > 250)
      {
         direction *= -1;
         distance = 0;
      }
      else 
         distance += dx * time;
   }
   else
   {
      if(abs(playerPosition.left - rect.left) > rect.width + 10) // rect.width >> atackRange;
         direction = (playerPosition.left - rect.left) / abs(playerPosition.left - rect.left);
      else
         dx = 0;
   }
   
   rect.left += dx * time;
   Vision.left += dx * time;
   CollisionX(location);
   if (!onGround) dy = dy + 0.005 * time;
   rect.top += dy * time;
   Vision.top = rect.top - characterHeight;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(rect.left, rect.top);
   visionRect.setPosition(Vision.left, Vision.top);
   if (direction < 0)
      Vision.left = rect.left - Vision.width;
   else
      Vision.left = rect.left + rect.width;

   
}
void Enemy::setDamageValue(int _damage)
{
   damageValue = _damage;
}
int Enemy::getDamageValue()
{
   return damageValue;
}
sf::FloatRect Enemy::getVision()
{
   return Vision;
}
void Enemy::setPlayerPosition(sf::FloatRect _PlayerPosition)
{
   playerPosition = _PlayerPosition;
}

void Enemy::CollisionX(std::vector<std::vector<Tile>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j].getTileType() == 1)
            if (dx > 0)
            {
               rect.left = j * 32 - rect.width;
               onGround = false;
               dy = -0.5;
            }
            else if (dx < 0)
            {
               rect.left = j * 32 + 32;
               onGround = false;
               dy = -0.5;
            }
}


void Enemy::CollisionY( std::vector<std::vector<Tile>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j].getTileType() == 1)
            if (dy > 0)
            {
               rect.top = i * 32 - rect.height;
               dy = 0;
               onGround = true;
            }
            else if (dy < 0)
            {
               rect.top = i * 32 + 32;
               dy = 0;
            }
}
