#include "GameObjectCreator.h"

SPtrGameObject ThornsCreator::factoryMethod(IntVector &coords) const
{
   SPtrGameObject tmp = std::make_shared<Thorns>();
   tmp->setX(0);
   tmp->setY(0);
   if(coords.size() == 2)
   {
      tmp->setX(coords[0]);
      tmp->setY(coords[1]);
   }
   return std::move(tmp);
}

SPtrGameObject TeleportCreator::factoryMethod(IntVector &coords) const
{
   SPtrGameObject tmp;
   tmp = std::make_shared<Teleport>(32, 0);
   tmp->setX(0);
   tmp->setY(0);
   if(coords.size() == 4)
   {
      tmp = std::make_shared<Teleport>(coords[0],coords[1]);
      tmp->setX(coords[2]);
      tmp->setY(coords[3]);
   }
   return tmp;
}
