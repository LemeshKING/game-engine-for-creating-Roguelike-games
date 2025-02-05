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


