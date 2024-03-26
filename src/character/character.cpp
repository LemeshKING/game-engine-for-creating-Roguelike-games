#include "character.h"

Character::Character()
{
}

void Character::update(const float &time, const std::vector<std::vector<int>>& location)
{
   rect.left += dx * time;
   CollisionX(location);
   if(!onGround) dy = dy + 0.005*time ;
   rect.top += dy * time;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(rect.left,rect.top);
   dx = 0;
}

void Character::CollisionX(const std::vector<std::vector<int>>& location)
{
   
}


void Character::CollisionY(const std::vector<std::vector<int>>& location)
{
}
