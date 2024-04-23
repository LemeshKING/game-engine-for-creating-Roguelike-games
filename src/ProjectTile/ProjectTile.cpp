#include "ProjectTile.h"
#include <iostream>

ProjectTile::ProjectTile()
{
   
}

void ProjectTile::setSprite(sf::RectangleShape _rectangle)
{
   rectangle = _rectangle;
}

sf::RectangleShape ProjectTile::getSprite()
{
   return rectangle;
}

sf::FloatRect ProjectTile::getRect()
{
   return hitBox;
}

void ProjectTile::setHitBox(sf::FloatRect _HitBox)
{
   hitBox = _HitBox;
}

void ProjectTile::update(const float time)
{
   if(distance < 400)
   {  
      hitBox.left += dx * direction.x * time;
      hitBox.top += dy * direction.y * time;
      distance += sqrt(dx * dx * time * time + dy * dy * time * time);
      rectangle.setPosition(hitBox.left, hitBox.top);
      rectangle.setRotation(angel);
   }
   else
   {
      std::cout << distance << std::endl;
      alive = false;
      distance = 0;
   }
}

void ProjectTile::Initialization(int x, int y)
{
   hitBox = sf::FloatRect(x, y, 20, 10);
   rectangle.setSize(sf::Vector2f(hitBox.width,hitBox.height));
   rectangle.setFillColor(sf::Color::Yellow);
   rectangle.setPosition(hitBox.left, hitBox.top);
   alive = true;
}

void ProjectTile::setDirection(sf::Vector2i _direction)
{
   direction = _direction;
}

bool ProjectTile::isAlive()
{
   return alive;
}
