#include "character.h"

Character::Character()
{
}

void Character::update(const float time, IntVectorVector& location)
{
   physicalQ.rect.left += physicalQ.dx * time;
   CollisionX(location);
   if(!onGround) physicalQ.dy = physicalQ.dy + 0.005*time ;
   physicalQ.rect.top += physicalQ.dy * time;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(physicalQ.rect.left, physicalQ.rect.top);
   physicalQ.dx = 0;
}

void Character::setDirection(int _direction)
{
   direction = _direction;
}

void Character::setDx(float _dx)
{
   physicalQ.dx = _dx;
}

void Character::setDy(float _dy)
{
   physicalQ.dy = _dy;
}

void Character::setCharacterHeight(int _CharacterHeight)
{
   characterHeight = _CharacterHeight;
}

void Character::setCharacterWidth(int _CharacterWidth)
{
   characterWidth = _CharacterWidth;
}

bool Character::isOnGround()
{
   return onGround;
}

sf::RectangleShape Character::getRectangle()
{
   return rectangle;
}

hlth::Health Character::getHealth()
{
   return health;
}

sf::FloatRect Character::getRect()
{
   return physicalQ.rect;
}

void Character::setHealth(hlth::Health _Health)
{
   health = _Health;
}

void Character::TakeDamage(int damageValue)
{  
   health.TakeDamage(damageValue);
   if (health.getHealthPoints() == 0)
      Kill();
}

bool Character::isAlive()
{
   return alive;
}

void Character::setRect(sf::FloatRect _rect)
{
   physicalQ.rect = _rect;
}

void Character::jump()
{
   onGround = false;
}

void Character::stateOnGround()
{
   onGround = true;
}

void Character::setLeft(float left)
{
   physicalQ.rect.left = left;
}

void Character::setTop(float top)
{
   physicalQ.rect.top = top;
}

float Character::getDx()
{
   return physicalQ.dx;
}

float Character::getDy()
{
   return physicalQ.dy;
}

int Character::getDirection()
{
    return direction;
}




void Character::CollisionX(IntVectorVector& location)
{
   for (int i = physicalQ.rect.top / 32; i < (physicalQ.rect.top + physicalQ.rect.height) / 32; i++)
      for (int j = physicalQ.rect.left / 32; j < (physicalQ.rect.left + physicalQ.rect.width) / 32; j++)
         if (location[i][j]== 1)
            if (physicalQ.dx > 0)
               physicalQ.rect.left = j * 32 - physicalQ.rect.width;
            else if (physicalQ.dx < 0)
               physicalQ.rect.left = j * 32 + 32;
}


void Character::CollisionY(IntVectorVector& location)
{
   for (int i = physicalQ.rect.top / 32; i < (physicalQ.rect.top + physicalQ.rect.height) / 32; i++)
      for (int j = physicalQ.rect.left / 32; j < (physicalQ.rect.left + physicalQ.rect.width) / 32; j++)
         if (location[i][j] == 1)
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

void Character::Kill()
{
   alive = false;
}

void Character::ChangeStateCharacter()
{

}
