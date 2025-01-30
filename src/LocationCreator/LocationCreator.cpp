#include "LocationCreator.h"

UPtrMap MeadowsCreator::factoryMethood(unsigned int& _Height, unsigned int& _Width, float& _Persistence, int& _Count, unsigned int& _seed)
{
   UPtrMap tmp = std::make_unique<Meadows>();
   tmp->setHeight(_Height);
   tmp->setWidth(_Width);
   tmp->setPersistence(_Persistence);
   tmp->setCountNoiseFunction(_Count);
   tmp->setSeed(_seed);
   tmp->GenerateLocation();
   return std::move(tmp);
}
