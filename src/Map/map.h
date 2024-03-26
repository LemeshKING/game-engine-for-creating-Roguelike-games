#pragma once
#include "../proceduralgeneration/ProceduralGeneration.h"
#include <random>
namespace mp{
   class Map
   {
   private:
      unsigned int seed = 0;
      unsigned int Height = 0, Width = 0;
      float persistence = 0;
      int countNoiseFunction = 0;
   public:
      std::vector<std::vector<int>> TileMap;

      void GenerateMap();
      unsigned int getHeight();
      unsigned int getWidth();
      void setHeight(unsigned int _Height);
      void setWidth(unsigned int _Width);
      void setPersistence(float _Persistence);
      void setCountNoiseFunction(int _Count);
      void setSeed(unsigned int _seed);
   private: 
      void smoothMap(std::vector<int>& tmp);
   
   };
}