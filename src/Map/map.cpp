#include "map.h"

void mp::Map::smoothMap()
{
	for (auto& i : MapHeightValues)
		if (i >= Height-3)
			i = Height - 6;
	
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

void mp::Map::GenerateCaves()
{
	
	CavesWidth = 50;
	int randomMapPoint = (int)pg::PerlinNoise1D(seed, persistence, countNoiseFunction) % (Width - CavesWidth);
	for(int i = 1; i < 5; i++)
		if(abs(MapHeightValues[randomMapPoint] - MapHeightValues[randomMapPoint + i]) == 1)
		{
			tryRnd++;
			randomMapPoint = (int)pg::PerlinNoise1D(seed + tryRnd, persistence, countNoiseFunction) % (Width - CavesWidth);
			i = 1;
		}
		
	std::vector<int> CavesHeight(CavesWidth);
	CavesHeight[0] = MapHeightValues[randomMapPoint];
	for(int i = randomMapPoint + 1; i < randomMapPoint + CavesWidth; i++)
			CavesHeight[i - randomMapPoint] = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction) % (CavesHeight[0] - 6));
	SmoothCaves(CavesHeight);
	sf::RectangleShape tmp;
	tmp.setFillColor(sf::Color::Black);
	tmp.setSize(sf::Vector2f(32, 32));
	for (int i = randomMapPoint; i < randomMapPoint + CavesWidth; i++)
	{
		tmp.setPosition(i * 32, (Height - 1 - CavesHeight[i - randomMapPoint]) * 32);
		TileMap[Height - 1 - CavesHeight[i - randomMapPoint]][i].setSprite(tmp);
		TileMap[Height - 1 - CavesHeight[i- randomMapPoint]][i].setType(1);
	}
	tmp.setFillColor(sf::Color::Blue);
	for(int i = randomMapPoint + 1; i < randomMapPoint + 5; i++)
	{
		tmp.setPosition(i * 32, (Height - 1 - MapHeightValues[i]) * 32);
		TileMap[Height - 1 - MapHeightValues[i]][i].setSprite(tmp);
		TileMap[Height - 1 - MapHeightValues[i]][i].setType(0);
	}

}

void mp::Map::SmoothCaves(std::vector<int>& Cave)
{
	for (int i = 1; i < Cave.size(); i++)
	{
		if (Cave[i] - Cave[i - 1] > 1)
			Cave[i] -= Cave[i] - Cave[i - 1] - 1;
		else if (Cave[i] - Cave[i - 1] < -1)
			Cave[i] += Cave[i - 1] - Cave[i] - 1;
	}
	for (int i = 2; i < Cave.size(); i++)
		if (Cave[i - 2] == Cave[i] && abs(Cave[i - 1] - Cave[i]) == 1)
			Cave[i - 1] = Cave[i];
}

void mp::Map::GenerateMap()
{
	srand(time(NULL));
	seed = 1 + std::rand() % 10000;
	TileMap.resize(Height);
	sf::RectangleShape tmp;
	tmp.setFillColor(sf::Color::Magenta);
	tmp.setSize(sf::Vector2f(32,32));
	for(auto &i: TileMap)
		i.resize(Width);
	for(int i = 0; i < Height; i++)
		for(int j = 0; j < Width; j++)
		{
			tmp.setPosition(j * 32, i * 32);
			TileMap[i][j].setSprite(tmp);
		}
   MapHeightValues.resize(Width);
   for(int i = 0; i < Width; i++)
		MapHeightValues[i] =abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction)) % Height;
   smoothMap();
	tmp.setFillColor(sf::Color::Black);
	for (int j = 0; j < Width; j++)
	{
		tmp.setPosition(j * 32, (Height - 1 - MapHeightValues[j]) * 32);
		TileMap[Height - 1 - MapHeightValues[j]][j].setSprite(tmp);
		TileMap[Height - 1 - MapHeightValues[j]][j].setType(1);
	}
	GenerateCaves();
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
