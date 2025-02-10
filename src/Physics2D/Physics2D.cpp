#include "Physics2D.h"



void gravity(PhysicalQuantities& pq, const float& time, const std::unique_ptr<mp::Map>& location)
{
   
   pq.dy = pq.dy + 0.0005 * time;
   pq.rect.top += pq.dy * time;
   Collision(pq, location);
}

void Collision(PhysicalQuantities& pq, const std::unique_ptr<mp::Map>& location)
{
   for(int i = pq.rect.top /32; i < (pq.rect.top + pq.rect.height) / 32; i++)
      for(int j = pq.rect.left / 32; j < (pq.rect.left + pq.rect.width) / 32; j++)
         if (location->TileMap[i][j].getTileType() == 1 || location->TileMap[i][j].getTileType() == 3)
         {
            pq.rect.top = i * 32 - pq.rect.height;
            pq.dy = -pq.dy * pq.elasticityCoefficient;
            break;
         }
}

void findingIntersections(Player &pl, const std::unique_ptr<mp::Map>& location)
{
   for (int i = (pl.physicalQ.rect.top - pl.physicalQ.rect.height)/ 32; i < (pl.physicalQ.rect.top + pl.physicalQ.rect.height) / 32; i++)
      for (int j = (pl.physicalQ.rect.left - pl.physicalQ.rect.width) / 32; j < (pl.physicalQ.rect.left + pl.physicalQ.rect.width) / 32; j++)
      {
         for(int objectIndex = 0; objectIndex < location->TileMap[i][j].objectsOnTile.size(); objectIndex++)
            if(pl.physicalQ.rect.intersects(location->TileMap[i][j].objectsOnTile[objectIndex]->physicalQ.rect))
               location->TileMap[i][j].objectsOnTile[objectIndex]->PlayerInteraction(pl); 
         if (location->TileMap[i][j].Weapon != nullptr)
            if (pl.physicalQ.rect.intersects(location->TileMap[i][j].Weapon->getRect()))
               if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pl.raisingFrames > 77)
               {
                  SPtrWeapon tmp = pl.getWeapon();
                  pl.setWeapon(location->TileMap[i][j].Weapon);
                  location->TileMap[i][j].Weapon = tmp;
                  pl.raisingFrames = 0;
               }
         for(int enemyIndex = 0; enemyIndex < location->TileMap[i][j].enemysOnTile.size(); enemyIndex++)
         {
            if(pl.physicalQ.rect.intersects(location->TileMap[i][j].enemysOnTile[enemyIndex]->physicalQ.rect))
               pl.TakeDamage(location->TileMap[i][j].enemysOnTile[enemyIndex]->getDamageValue());
            if(pl.getWeapon()->physicalQ.rect.intersects(location->TileMap[i][j].enemysOnTile[enemyIndex]->physicalQ.rect) && pl.key["Attack"] && pl.animation.getAnimation().getFrame() > 2 && !location->TileMap[i][j].enemysOnTile[enemyIndex]->wasAttaking)
            {
               location->TileMap[i][j].enemysOnTile[enemyIndex]->TakeDamage(pl.getWeapon()->getDamageValue());
               location->TileMap[i][j].enemysOnTile[enemyIndex]->wasAttaking = true;
               

            }
            if(!pl.key["Attack"])
               location->TileMap[i][j].enemysOnTile[enemyIndex]->wasAttaking = false;
         }
               
            
         
      }



}


