#include "enemy.h"

void Enemy::SawPlayer(bool _sawPlayer)
{
   playerAlive = _sawPlayer;
   sawPlayer = _sawPlayer;
}

void Enemy::Initialization(int x, int y)
{
   cost = 100;

   physicalQ.rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   Vision = sf::FloatRect(x + characterWidth, y - characterHeight, 200, 200);
   
   if(!texture.loadFromFile("../src/enemy/enemy.png"))
      texture.loadFromFile("../../src/enemy/enemy.png");
   animation.setTexture(texture);
   animation.CreateAnimation("walk",0,0,characterWidth,characterHeight,5,0.01);
   animation.CreateAnimation("attack",0,50,characterWidth,characterHeight,5,0.0045);
   positionX = x / 32;
   positionY = y / 32;
   CharacterState = walk;
   physicalQ.dx = 0.15;
}

void Enemy::update(const float time, IntVectorVector& location)
{
   if(CharacterState == walk) animation.setAnimation("walk");
   if(CharacterState == attack) animation.setAnimation("attack");
   animation.flipAnimation(direction < 0);
   animation.tick(time);
   physicalQ.dx = 0.15 * direction;
   if(Vision.intersects(playerPosition) && !sawPlayer && playerAlive)
      sawPlayer = true;
   if(!sawPlayer)
   {  
      if(abs(distance) > 250)
      {
         direction *= -1;
         distance = 0;
      }
      else 
         distance += physicalQ.dx * time;
   }
   else
   {
      if(direction == -1)
         if(abs(playerPosition.left - physicalQ.rect.left) > AttackRange) // rect.width >> atackRange;
         {
            direction = (playerPosition.left - physicalQ.rect.left) / abs(playerPosition.left - physicalQ.rect.left);
         }
         else 
            CharacterState = attack;
      else if (abs(playerPosition.left - physicalQ.rect.left) > physicalQ.rect.width + 1) // rect.width >> atackRange;
      {
         direction = (playerPosition.left - physicalQ.rect.left) / abs(playerPosition.left - physicalQ.rect.left);
      }
      else
         CharacterState = attack;
   }
   if (CharacterState == attack && chardgeAttack == 0)
      animation.setFrame(0);
   if (CharacterState == attack)
   {
      physicalQ.dx = 0;
      chardgeAttack++;
      Attack();
   }


   physicalQ.rect.left += physicalQ.dx * time;
   Vision.left += physicalQ.dx * time;
   CollisionX(location);
   if (!onGround) physicalQ.dy = physicalQ.dy + 0.005 * time;
   physicalQ.rect.top += physicalQ.dy * time;
   Vision.top = physicalQ.rect.top - characterHeight;
   onGround = false;
   CollisionY(location);
   animation.setPosition(physicalQ.rect.left, physicalQ.rect.top);
   if (direction < 0)
      Vision.left = physicalQ.rect.left - Vision.width;
   else
      Vision.left = physicalQ.rect.left + physicalQ.rect.width;
   positionX = (int)physicalQ.rect.left / 32;
   positionY = (int)physicalQ.rect.top / 32;
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

unsigned int Enemy::getCost()
{
   return cost;
}

void Enemy::CollisionX(IntVectorVector& location)
{
   for (int i = physicalQ.rect.top / 32; i < (physicalQ.rect.top + physicalQ.rect.height) / 32; i++)
      for (int j = physicalQ.rect.left / 32; j < (physicalQ.rect.left + physicalQ.rect.width) / 32; j++)
         if (location[i][j] == 1 || location[i][j] == 3)
         {
            if (physicalQ.dx > 0)
               physicalQ.rect.left = j * 32 - physicalQ.rect.width;
            else if (physicalQ.dx < 0)
               physicalQ.rect.left = j * 32 + 32;
            if (onGround)
            {
               physicalQ.dy = -0.65;
               onGround = false;
            }
         }
}


void Enemy::CollisionY(IntVectorVector& location)
{
   for (int i = physicalQ.rect.top / 32; i < (physicalQ.rect.top + physicalQ.rect.height) / 32; i++)
      for (int j = physicalQ.rect.left / 32; j < (physicalQ.rect.left + physicalQ.rect.width) / 32; j++)
         if (location[i][j] == 1 || location[i][j] == 3)
         {
            if (physicalQ.dy > 0)
            {
               physicalQ.rect.top = i * 32 - physicalQ.rect.height;
               physicalQ.dy = 0;
               onGround = true;
            }
            else if (physicalQ.dy < 0)
            {
               physicalQ.rect.top = i * 32 + 32;
               physicalQ.dy = 0;
            }
         }
         else if (location[i][j] == 4)
         {
            if (physicalQ.dx > 0)
               physicalQ.rect.left = j * 32 - physicalQ.rect.width;
            else if (physicalQ.dx < 0)
               physicalQ.rect.left = j * 32 + 32;

            distance = 0;
            direction *= -1;
         }
}

void Enemy::Attack()
{
   if(chardgeAttack > 144)
   {
      physicalQ.dx = 0.25 * direction;
      attacking = false;
      chardgeAttack = 0;
      CharacterState = walk;
   }
}
