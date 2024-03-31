#include "enemy.h"

void Enemy::Initialization(int x, int y)
{
   rectangle.setFillColor(sf::Color::Red);
   rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   rectangle.setSize(sf::Vector2f(rect.width,rect.height));
   rectangle.setPosition(sf::Vector2f(rect.left,rect.top));
   dx = 0.35;
}

void Enemy::update(const float& time, const std::vector<std::vector<int>>& location)
{
   if(abs(distance) > 250)
      {
         direction*= -1;
         distance = 0;
         dx *= direction;
      }
   rect.left += dx * time;
   distance += dx * time;
   CollisionX(location);
   if (!onGround) dy = dy + 0.005 * time;
   rect.top += dy * time;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(rect.left, rect.top);
}
void Enemy::setDamageValue(int _damage)
{
   damageValue = _damage;
}
int Enemy::getDamageValue()
{
   return damageValue;
}
void Enemy::CollisionX(const std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1)
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


void Enemy::CollisionY(const std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1)
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
