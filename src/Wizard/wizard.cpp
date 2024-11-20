#include "wizard.h"
#include<iostream>

void Wizard::update(const float time, IntVectorVector& location)
{
   if (CharacterState == walk) animation.setAnimation("walk");
   if (CharacterState == attack) animation.setAnimation("attack");
   if (CharacterState == stay) animation.setAnimation("stay");
   animation.flipAnimation(direction < 0);
   animation.tick(time);
   dx = 0.1 * direction;
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
         distance += dx * time;
   }
   else
   {
      CharacterState = walk;
      direction = (playerPosition.left - rect.left) / abs(playerPosition.left - rect.left);
      directionAtack.x = (playerPosition.left /*+ playerPosition.width / 2*/ - rect.left) / abs(rect.left - playerPosition.left /*- playerPosition.width / 2*/);
      directionAtack.y = (playerPosition.top + playerPosition.height / 2 - rect.top) / abs(rect.top - playerPosition.top - playerPosition.height / 2);
      if (abs(playerPosition.left - rect.left) < AttackRange && !projectTile.isAlive())
            attacking = true;
      
      else if(projectTile.isAlive())
      {
         dx = 0;
         CharacterState = stay;
      }

       
      

   }

   if (attacking)
   {
      CharacterState = attack;
      dx = 0;
      chardgeAttack++;
      Attack();
   }
   if (chardgeAttack > 144)
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
   animation.setPosition(rect.left, rect.top);
   if (direction < 0)
      Vision.left = rect.left - Vision.width;
   else
      Vision.left = rect.left + rect.width;

}

void Wizard::Initialization(int x, int y)
{
   rectangle.setFillColor(sf::Color::Color(225,70,70));
   rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   Vision = sf::FloatRect(x + characterWidth, y - characterHeight, 400, 400);
   rectangle.setSize(sf::Vector2f(rect.width, rect.height));
   rectangle.setPosition(sf::Vector2f(rect.left, rect.top));
   if (!texture.loadFromFile("../src/enemy/enemy.png"))
      texture.loadFromFile("../../src/enemy/enemy.png");
   animation.setTexture(texture);
   animation.CreateAnimation("walk", 0, 0, characterWidth, characterHeight, 5, 0.01);
   animation.CreateAnimation("attack", 0, 50, characterWidth, characterHeight, 5, 0.0045);
   animation.CreateAnimation("stay",0,0,characterWidth,characterHeight,1,0.0);
   CharacterState = walk;
   dx = 0.1;
}

void Wizard::Attack()
{

   if (chardgeAttack > 144)
   {
      if (directionAtack.y == 0)
         directionAtack.y = 1;
      projectTile.Initialization(rect.left, rect.top);
      projectTile.setDirection(directionAtack);
      float length = sqrt((playerPosition.left + playerPosition.width / 2 - rect.left) * (playerPosition.left + playerPosition.width / 2 - rect.left) + (playerPosition.top + playerPosition.height / 2 - rect.top) * (playerPosition.top + playerPosition.height / 2 - rect.top));
      projectTile.dx = abs(playerPosition.left + playerPosition.width / 2 - rect.left) / length * 0.35;
      projectTile.dy = abs(playerPosition.top + playerPosition.height / 2 - rect.top) / length * 0.35;
      float dotProduct = (playerPosition.left + playerPosition.width / 2 - rect.left) * (playerPosition.left + playerPosition.width / 2 - rect.left);
     /* projectTile.angel = acos(dotProduct / (length * (playerPosition.left + playerPosition.width / 2 - rect.left))) * 180 / 3.141592653589793;*/
      projectTile.angel = acos((playerPosition.left + playerPosition.width / 2 - rect.left) / length) * 180/ 3.141592653589793;
      if(directionAtack.y < 0)
         projectTile.angel *= -1;
      attacking = false;
      chardgeAttack = 0;
   }
}
