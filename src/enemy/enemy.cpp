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

   dx = 0.15;
}

void Enemy::update(const float time, std::vector<std::vector<int>>& location)
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
      if(direction == -1)
         if(abs(playerPosition.left - rect.left) > AttackRange) // rect.width >> atackRange;
         {
            direction = (playerPosition.left - rect.left) / abs(playerPosition.left - rect.left);
         }
         else 
            attacking = true;
      else if (abs(playerPosition.left - rect.left) >  rect.width + 1) // rect.width >> atackRange;
      {
         direction = (playerPosition.left - rect.left) / abs(playerPosition.left - rect.left);
      }
      else
         attacking = true;
   }

   if (attacking)
   {
      dx = 0;
      chardgeAttack++;
      Attack();
   }
   if(chardgeAttack > 144)
      attackCooldown++;
   rect.left += dx * time;
   Vision.left += dx * time;
   CollisionX(location);
   if (!onGround) dy = dy + 0.005 * time;
   rect.top += dy * time;
   Vision.top = rect.top - characterHeight;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(rect.left, rect.top);
   if (direction < 0)
      Vision.left = rect.left - Vision.width;
   else
      Vision.left = rect.left + rect.width;

   
}
void Enemy::TakeDamage(int damageValue)
{
   if(rand() % 10 == 0)
      chardgeAttack = 0;
   health.TakeDamage(damageValue);
   if (health.getHealthPoints() == 0)
      Kill();
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

void Enemy::CollisionX(std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1 || location[i][j] == 3)
         {
            if (dx > 0)
               rect.left = j * 32 - rect.width;
            else if (dx < 0)
               rect.left = j * 32 + 32;
            if (onGround)
            {
               dy = -0.65;
               onGround = false;
            }
         }
}


void Enemy::CollisionY( std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1 || location[i][j] == 3)
         {
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
         else if (location[i][j] == 4)
         {
            if (dx > 0)
               rect.left = j * 32 - rect.width;
            else if (dx < 0)
               rect.left = j * 32 + 32;

            distance = 0;
            direction *= -1;
         }
}

void Enemy::Attack()
{
   if(chardgeAttack > 144)
   {
      dx = 0.25 * direction;
      attacking = false;
      chardgeAttack = 0;
   }
}
