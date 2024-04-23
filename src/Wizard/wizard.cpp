#include "wizard.h"

void Wizard::update(const float time, std::vector<std::vector<int>>& location)
{
   dx = 0.15 * direction;
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
      direction = (playerPosition.left - rect.left) / abs(playerPosition.left - rect.left);
      directionAtack.x = (playerPosition.left + playerPosition.width / 2 - rect.left) / abs(rect.left - playerPosition.left - playerPosition.width / 2);
      if ((playerPosition.top + playerPosition.height / 2 - rect.top))
         directionAtack.y = 0;
      directionAtack.y = (playerPosition.top + playerPosition.height / 2 - rect.top) / abs(rect.top - playerPosition.top - playerPosition.height / 2);
      if (abs(playerPosition.left - rect.left) < AttackRange && !projectTile.isAlive())
            attacking = true;
      
      else if(projectTile.isAlive())
         dx = 0;

       
      

   }

   if (attacking)
   {
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
   if (direction < 0)
      Vision.left = rect.left - Vision.width;
   else
      Vision.left = rect.left + rect.width;

}

void Wizard::Initialization(int x, int y)
{
   rectangle.setFillColor(sf::Color::Red);
   rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   Vision = sf::FloatRect(x + characterWidth, y - characterHeight, 400, 400);
   rectangle.setSize(sf::Vector2f(rect.width, rect.height));
   rectangle.setPosition(sf::Vector2f(rect.left, rect.top));

   dx = 0.15;
}

void Wizard::Attack()
{
   if (chardgeAttack > 144)
   {
      projectTile.Initialization(rect.left, rect.top);
      projectTile.setDirection(directionAtack);
      float length = sqrt((playerPosition.left + playerPosition.width / 2 - rect.left) * (playerPosition.left + playerPosition.width / 2 - rect.left) + (playerPosition.top + playerPosition.height / 2 - rect.top) * (playerPosition.top + playerPosition.height / 2 - rect.top));
      projectTile.dx = abs(playerPosition.left + playerPosition.width / 2 - rect.left) / length * 0.25;
      projectTile.dy = abs(playerPosition.top + playerPosition.height / 2 - rect.top) / length * 0.25;
      float dotProduct = (playerPosition.left + playerPosition.width / 2 - rect.left) * (playerPosition.left + playerPosition.width / 2 - rect.left);
      projectTile.angel = acos(dotProduct / (length * (playerPosition.left + playerPosition.width / 2 - rect.left))) * 180 / 3.141592653589793;
      if(direction == 1)
         projectTile.angel *=-1;
      attacking = false;
      chardgeAttack = 0;
   }
}
