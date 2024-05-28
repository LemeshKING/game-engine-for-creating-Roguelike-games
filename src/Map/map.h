#pragma once
#include "../proceduralgeneration/ProceduralGeneration.h"
#include "../Tile/Tile.h"
#include "../Wizard/wizard.h"
#include "../thorns/thorns.h"
#include "../teleport/teleport.h"
#include "../sword/sword.h"
#include <random>
namespace mp{
   class Map
   {
   private:
      std::vector<Enemy*> Enemys;

      int countEnemys;
      unsigned int seed = 0;
      unsigned int Height = 0, Width = 0;
      float persistence = 0;
      int countNoiseFunction = 0;
      int startPlayerPosition;
      sf::Texture texture;
   public:
      int currentEnemy = 0;
      int countCaves = 0;
      int CavesWidth = 0;
      bool canGenerateCave = true;
      int randomMapPoint;
      std::vector<int> rndMapPoints;
   public:
      std::vector<std::vector<int>> TypeOfTiles;
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
      unsigned int getSeed();
      int getStartPlayerPosition();
      std::vector<Enemy*> getEnemys();
   private: 
      void smoothMap();
      void GenerateCaves();
      void SmoothCaves(std::vector<int> &Cave);
      void FillMap();
   };
}