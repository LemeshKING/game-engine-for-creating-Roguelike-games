#pragma once
#include "../proceduralgeneration/ProceduralGeneration.h"
#include "../Tile/Tile.h"
#include "../sword/sword.h"
#include "EnemyCreator.h"
#include "GameObjectCreator.h"
#include <random>

typedef std::vector<IntVector> IntVectorVector;
typedef std::vector<UPtrEnemy> UPtrEnemyVector;
typedef std::unique_ptr<EnemyCreator> UPtrEnemyCreator;
typedef std::unique_ptr<GameObjectCreator> UPtrGameObjectCreator;

namespace mp
{
   class Map
   {
   protected:
      UPtrEnemyVector _Enemys;
      UPtrEnemyCreator creatorEnemys;
      UPtrGameObjectCreator creatorGameObjects;
      int countEnemys;
      unsigned int seed = 0;
      unsigned int Height = 0, Width = 0;
      float persistence = 0;
      int countNoiseFunction = 0;
      int startPlayerPosition;
      sf::Texture texture;

      int countCaves = 0;
      int CavesWidth = 0;
      bool canGenerateCave = true;
      int randomMapPoint;
      IntVector rndMapPoints;
      virtual void smoothMap() = 0;
      virtual void FillMap() = 0;
   public:
      int currentEnemy = 0;
      IntVectorVector TypeOfTiles;
      int tryRnd = 0;
      std::vector<std::vector<Tile>> TileMap;
      IntVector MapHeightValues;
      virtual void GenerateLocation() = 0;
      unsigned int getHeight();
      unsigned int getWidth();
      void setHeight(unsigned int _Height);
      void setWidth(unsigned int _Width);
      void setPersistence(float _Persistence);
      void setCountNoiseFunction(int _Count);
      void setSeed(unsigned int _seed);
      unsigned int getSeed();
      int getStartPlayerPosition();
      UPtrEnemyVector getEnemys();
   private: 
      
      //void GenerateCaves();
      //void SmoothCaves(IntVector &Cave);
      
   };
}