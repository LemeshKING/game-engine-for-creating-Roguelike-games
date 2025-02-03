#include "map.h"




SPtrEnemyVector mp::Map::getEnemys()
{
	return std::move(_Enemys);
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

unsigned int mp::Map::getSeed()
{
	return seed;
}

int mp::Map::getStartPlayerPosition()
{
	return startPlayerPosition;
}
