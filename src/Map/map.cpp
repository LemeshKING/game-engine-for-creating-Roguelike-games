#include "map.h"

void mp::Map::smoothMap()
{
	for (auto& i : MapHeightValues)
	{
		if (i <= 0)
			i = 1;
		else if (i >= Height-3)
			i = Height - 6;
	}
	for (int i = 1; i < Width; i++)
	{
		if (MapHeightValues[i] - MapHeightValues[i - 1] > 1)
			MapHeightValues[i] -= MapHeightValues[i] - MapHeightValues[i - 1] - 1;
		else if (MapHeightValues[i] - MapHeightValues[i - 1] < -1)
			MapHeightValues[i] += MapHeightValues[i - 1] - MapHeightValues[i] - 1;
	}
	for (int i = 2; i < Width; i++)
		if (MapHeightValues[i - 2] == MapHeightValues[i] && abs(MapHeightValues[i - 1] - MapHeightValues[i]) == 1)
			MapHeightValues[i - 1] = MapHeightValues[i];
	startPlayerPosition = Height - MapHeightValues[0] - 1;
}

void mp::Map::GenerateMap()
{
	srand(time(NULL));
	seed = 1 + std::rand() % 10000;
	TileMap.resize(Height);
	for(auto &i: TileMap)
		i.resize(Width);
   MapHeightValues.resize(Width);
   for(int i = 0; i < Width; i++)
		MapHeightValues[i] = pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction);
   smoothMap();
	srand(time(NULL));
	int seed = 1 + std::rand() % 10000;
	for (int j = 0; j < Width; j++)
		TileMap[Height - 1 - MapHeightValues[j]][j] = 1;
}

unsigned int mp::Map::getHeight()
{
	return Height;
}

unsigned int mp::Map::getWidth()
{
	return Width;
}

void mp::Map::setHeight(unsigned int _Height)
{
	Height = _Height;
}

void mp::Map::setWidth(unsigned int _Width)
{
	Width = _Width;
}

void mp::Map::setPersistence(float _Persistence)
{
	persistence = _Persistence;
}

void mp::Map::setCountNoiseFunction(int _Count)
{
	countNoiseFunction = _Count;
}

void mp::Map::setSeed(unsigned int _seed)
{
	seed = _seed;
}

int mp::Map::getStartPlayerPosition()
{
	return startPlayerPosition;
}
