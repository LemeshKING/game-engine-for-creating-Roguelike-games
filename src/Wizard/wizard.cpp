#include "wizard.h"
#include<iostream>

void Wizard::update(const float time, IntVectorVector& location)
{
   if (CharacterState == walk) animation.setAnimation("walk");
   if (CharacterState == attack) animation.setAnimation("attack");
   if (CharacterState == stay) animation.setAnimation("stay");
   animation.flipAnimation(direction < 0);
   animation.tick(time);
   physicalQ.dx = 0.1 * direction;
   if (Vision.intersects(playerPosition) && !sawPlayer)
      sawPlayer = true;
   if (!sawPlayer)
   {
      if (abs(distance) > 250)
      {
         direction *= -1;
         distance = 0;
      }
      else
         distance += physicalQ.dx * time;
   }
   else
   {
      CharacterState = walk;
      direction = (playerPosition.left - physicalQ.rect.left) / abs(playerPosition.left - physicalQ.rect.left);
      directionAtack.x = (playerPosition.left /*+ playerPosition.width / 2*/ - physicalQ.rect.left) / abs(physicalQ.rect.left - playerPosition.left /*- playerPosition.width / 2*/);
      directionAtack.y = (playerPosition.top + playerPosition.height / 2 - physicalQ.rect.top) / abs(physicalQ.rect.top - playerPosition.top - playerPosition.height / 2);
      if (abs(playerPosition.left - physicalQ.rect.left) < AttackRange && !projectTile.isAlive())
            attacking = true;
      
      else if(projectTile.isAlive())
      {
         physicalQ.dx = 0;
         CharacterState = stay;
      }

       
      

   }

   if (attacking)
   {
      CharacterState = attack;
      physicalQ.dx = 0;
      chardgeAttack++;
      Attack();
   }
   if (chardgeAttack > 144)
      attackCooldown++;
   physicalQ.rect.left += physicalQ.dx * time;
   Vision.left += physicalQ.dx * time;
   CollisionX(location);
   if (!onGround) physicalQ.dy = physicalQ.dy + 0.005 * time;
   physicalQ.rect.top += physicalQ.dy * time;
   Vision.top = physicalQ.rect.top - characterHeight;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(physicalQ.rect.left, physicalQ.rect.top);
   animation.setPosition(physicalQ.rect.left, physicalQ.rect.top);
   if (direction < 0)
      Vision.left = physicalQ.rect.left - Vision.width;
   else
      Vision.left = physicalQ.rect.left + physicalQ.rect.width;
   //position = rect.left / 32 + rect.top / 32 * 250;

}

void Wizard::Initialization(int x, int y)
{
   cost = 125;
   physicalQ.rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   Vision = sf::FloatRect(x + characterWidth, y - characterHeight, 400, 400);
   if (!texture.loadFromFile("../src/enemy/enemy.png"))
      texture.loadFromFile("../../src/enemy/enemy.png");
   animation.setTexture(texture);
   animation.CreateAnimation("walk", 0, 0, characterWidth, characterHeight, 5, 0.01);
   animation.CreateAnimation("attack", 0, 50, characterWidth, characterHeight, 5, 0.0045);
   animation.CreateAnimation("stay",0,0,characterWidth,characterHeight,1,0.0);
   CharacterState = walk;
   //position = x / 32 + y / 32 * 250;
   physicalQ.dx = 0.1;
}

void Wizard::Attack()
{

   if (chardgeAttack > 144)
   {
      if (directionAtack.y == 0)
         directionAtack.y = 1;
      projectTile.Initialization(physicalQ.rect.left, physicalQ.rect.top);
      projectTile.setDirection(directionAtack);
      float length = sqrt((playerPosition.left + playerPosition.width / 2 - physicalQ.rect.left) * (playerPosition.left + playerPosition.width / 2 - physicalQ.rect.left) + (playerPosition.top + playerPosition.height / 2 - physicalQ.rect.top) * (playerPosition.top + playerPosition.height / 2 - physicalQ.rect.top));
      projectTile.dx = abs(playerPosition.left + playerPosition.width / 2 - physicalQ.rect.left) / length * 0.35;
      projectTile.dy = abs(playerPosition.top + playerPosition.height / 2 - physicalQ.rect.top) / length * 0.35;
      float dotProduct = (playerPosition.left + playerPosition.width / 2 - physicalQ.rect.left) * (playerPosition.left + playerPosition.width / 2 - physicalQ.rect.left);
     /* projectTile.angel = acos(dotProduct / (length * (playerPosition.left + playerPosition.width / 2 - rect.left))) * 180 / 3.141592653589793;*/
      projectTile.angel = acos((playerPosition.left + playerPosition.width / 2 - physicalQ.rect.left) / length) * 180/ 3.141592653589793;
      if(directionAtack.y < 0)
         projectTile.angel *= -1;
      attacking = false;
      chardgeAttack = 0;
   }
}
