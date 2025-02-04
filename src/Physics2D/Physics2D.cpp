#include "Physics2D.h"

void gravity(SPtrWeapon& weapon, const float& time, const std::unique_ptr<mp::Map>& location)
{
   float dy = 1;
   dy = dy + 0.0005 * time;
   sf::FloatRect tmp = weapon->getRect();
   tmp.top += dy;
   weapon->setRect(tmp);
   Collision(weapon, location);

}

void gravity(SPtrGameObject& gameObject, const float& time, const std::unique_ptr<mp::Map>& location)
{
   float dy = 3;
   dy = dy + 0.0005 * time;
   gameObject->setY(gameObject->getY() + dy);
   Collision(gameObject, location);

}

void gravity(Character& character, const float& time, const std::unique_ptr<mp::Map>& location)
{
   
}

void Collision(SPtrGameObject& gameObject, const std::unique_ptr<mp::Map>& location)
{
   for(int i = gameObject->getY() / 32; i < (gameObject->getY() + gameObject->getSprite().getGlobalBounds().height) / 32; i++)
      for(int j = gameObject->getX() / 32; j < (gameObject->getX() + gameObject->getSprite().getGlobalBounds().width) / 32; j++)
         if (location->TileMap[i][j].getTileType() == 1 || location->TileMap[i][j].getTileType() == 3)
            gameObject->setY(i * 32 - gameObject->getSprite().getGlobalBounds().height);
         
}

void Collision(SPtrWeapon& weapon, const std::unique_ptr<mp::Map>& location)
{
   for (int i = weapon->getRect().top / 32; i < (weapon->getRect().top + weapon->getRect().height) / 32; i++)
      for (int j = weapon->getRect().left / 32; j < (weapon->getRect().left + weapon->getRect().width) / 32; j++)
         if (location->TileMap[i][j].getTileType() == 1 || location->TileMap[i][j].getTileType() == 3)
            weapon->setRect(sf::FloatRect(weapon->getRect().left, i * 32 - weapon->getRect().height, weapon->getRect().width, weapon->getRect().height));
}


