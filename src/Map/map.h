#pragma once
#include "../proceduralgeneration/ProceduralGeneration.h"
#include "../Tile/Tile.h"
#include <random>
namespace mp{
   class Map
   {
   private:
      unsigned int seed = 0;
      unsigned int Height = 0, Width = 0;
      float persistence = 0;
      int countNoiseFunction = 0;
      int startPlayerPosition;
      int countCaves = 0;
      int CavesWidth = 0;
      bool canGenerateCave = true;
     
   public:
      int tryRnd = 0;
      std::vector<std::vector<Tile>> TileMap;
      std::vector<int> MapHeightValues;
      void GenerateMap();
      unsigned int getHeight();
      unsigned int getWidth();
      void setHeight(unsigned int _Height);
      void setWidth(unsigned int _Width);
      void setPersistence(float _Persistence);
      void setCountNoiseFunction(int _Count);
      void setSeed(unsigned int _seed);
      int getStartPlayerPosition();
   private: 
      void smoothMap();
      void GenerateCaves();
      void SmoothCaves(std::vector<int> &Cave);
   
   };
}