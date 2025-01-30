#pragma once

#include"../Meadows/Meadows.h"

typedef std::unique_ptr<mp::Map> UPtrMap;

class LocationCreator
{
 public:
   virtual ~LocationCreator() {};
   virtual UPtrMap factoryMethood(unsigned int &_Height, unsigned int &_Width, float &_Persistence, int &_Count, unsigned int &_seed) = 0;
};

class MeadowsCreator : public LocationCreator
{
public:
   virtual ~MeadowsCreator() {};
   virtual UPtrMap factoryMethood(unsigned int& _Height, unsigned int& _Width, float& _Persistence, int& _Count, unsigned int& _seed) override;
};
