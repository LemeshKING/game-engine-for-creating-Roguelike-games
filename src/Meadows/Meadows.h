#pragma once

#include "../Map/map.h"

class Meadows : public mp::Map
{
protected:
   void FillMap() override;
   void GenerateLocation() override;
   void smoothMap() override;
   void GenerateCaves();
   void SmoothCaves(IntVector& Cave);
};