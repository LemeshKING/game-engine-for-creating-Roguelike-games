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
	
	CavesWidth = 100;
	countCaves = Width / CavesWidth;
	rndMapPoints.resize(countCaves);
	rndMapPoints[0] = abs((int)pg::PerlinNoise1D(seed, persistence, countNoiseFunction)) % (CavesWidth);
	for (int i = 1; i < 6; i++)
		if (abs(MapHeightValues[rndMapPoints[0]] - MapHeightValues[rndMapPoints[0] + i]) > 0)
		{
			tryRnd++;
			rndMapPoints[0] = (int)pg::PerlinNoise1D(seed + tryRnd, persistence, countNoiseFunction) % (Width - CavesWidth);
			i = 1;
		}
	for (int k = 1; k < countCaves; k++)
	{
		int checkGeneration = Width - 2 * CavesWidth - rndMapPoints[k - 1] - 1;
		if(checkGeneration <= 0)
		{
			rndMapPoints.resize(--countCaves);
			k--;
			continue;
		}
		rndMapPoints[k] = rndMapPoints[k - 1] + CavesWidth + 1 + abs((int)pg::PerlinNoise1D(seed * k, persistence, countNoiseFunction)) % (Width - 2 * CavesWidth - rndMapPoints[k - 1] - 1);
		for (int i = 1; i < 6; i++)
			if (abs(MapHeightValues[rndMapPoints[k]] - MapHeightValues[rndMapPoints[k] + i]) > 0)
			{
				tryRnd++;
				rndMapPoints[k] = rndMapPoints[k - 1] + CavesWidth + 1 + abs((int)pg::PerlinNoise1D(seed + tryRnd, persistence, countNoiseFunction)) % (Width - 2 * CavesWidth - rndMapPoints[k - 1] - 1);
				i = 1;
				if (tryRnd > 100)
				{
					rndMapPoints.resize(--countCaves);
					k--;
					break;
				}
			}
	}

		
	
	
	for(int k = 0; k < countCaves; k++)
	{
		std::vector<int> CavesHeight(CavesWidth);
		CavesHeight[0] = MapHeightValues[rndMapPoints[k]];
		for(int i = rndMapPoints[k] + 1; i < rndMapPoints[k] + CavesWidth; i++)
			CavesHeight[i - rndMapPoints[k]] = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction) % (CavesHeight[0] - 6));
		SmoothCaves(CavesHeight);
		sf::RectangleShape tmp;
		tmp.setFillColor(sf::Color::Black);
		tmp.setSize(sf::Vector2f(32, 32));
		for (int i = rndMapPoints[k]; i < rndMapPoints[k] + CavesWidth; i++)
		{
			tmp.setPosition(i * 32, (Height - 1 - CavesHeight[i - rndMapPoints[k]]) * 32);
			TileMap[Height - 1 - CavesHeight[i - rndMapPoints[k]]][i].setSprite(tmp);
			TileMap[Height - 1 - CavesHeight[i- rndMapPoints[k]]][i].setType(1);
		}

		for (int i = MapHeightValues[rndMapPoints[k] + CavesWidth - 1]; i > 0; i--)
		{
			tmp.setPosition((rndMapPoints[k] + CavesWidth - 1) * 32, (Height - 1 - i) * 32);
			TileMap[Height - 1 - i][rndMapPoints[k] + CavesWidth - 1].setSprite(tmp);
			TileMap[Height - 1 - i][rndMapPoints[k] + CavesWidth - 1].setType(3);
		}

		for (int i = rndMapPoints[k]; i < rndMapPoints[k] + CavesWidth - 1; i++)
		{
			for (int j = MapHeightValues[i] - 1; j > CavesHeight[i - rndMapPoints[k]] + 5; j--)
			{
				tmp.setPosition(i * 32, (Height - 1 - j) * 32);
				TileMap[Height - 1 - j][i].setSprite(tmp);
				TileMap[Height - 1 - j][i].setType(3);
			}
			for (int j = CavesHeight[i - rndMapPoints[k]] - 1; j > 0; j--)
			{
				tmp.setPosition(i * 32, (Height - 1 - j) * 32);
				TileMap[Height - 1 - j][i].setSprite(tmp);
				TileMap[Height - 1 - j][i].setType(3);
			}
		}
		tmp.setFillColor(sf::Color::Magenta);
		for(int i = rndMapPoints[k] + 1; i < rndMapPoints[k] + 5; i++)
		{
			tmp.setPosition(i * 32, (Height - 1 - MapHeightValues[i]) * 32);
			TileMap[Height - 1 - MapHeightValues[i]][i].setSprite(tmp);
			TileMap[Height - 1 - MapHeightValues[i]][i].setType(0);
		}
		for (int i = 10; i < CavesWidth - 5; i++)
		{
			if(currentEnemy < countEnemys)
			{
				int isSpawnEnemy = abs((int)pg::PerlinNoise1D(i * seed, persistence,countNoiseFunction)) % 100;
				if (isSpawnEnemy > 70)
				{
					hlth::Health health;
					health.setHealthPoints(100);
					Enemys[currentEnemy].setHealth(health);
					Enemys[currentEnemy].setCharacterHeight(50);
					Enemys[currentEnemy].setCharacterWidth(40);
					Enemys[currentEnemy].setDamageValue(10);
					Enemys[currentEnemy].Initialization((i + rndMapPoints[k]) * 32, (Height - CavesHeight[i] - 3) * 32);
					currentEnemy++;
				}
			}
			else
				break;
		}
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

void mp::Map::FillMap()
{
	sf::RectangleShape tmp(sf::Vector2f(32,32));
	tmp.setFillColor(sf::Color::Color(55,72,32));
	for(int i = 3; i < Width; i++)
		if((MapHeightValues[i - 3] == MapHeightValues[i]) && (MapHeightValues[i - 3] - MapHeightValues[i - 2] == 1) && (MapHeightValues[i] - MapHeightValues[i - 1] == 1))
		{
			tmp.setPosition((i-2) * 32, (Height - 2 -MapHeightValues[i - 2]) * 32);
			TileMap[Height - 2 - MapHeightValues[i - 2]][i - 2].setSprite(tmp);
			TileMap[Height - 2 - MapHeightValues[i - 2]][i - 2].setType(4);
			tmp.setPosition((i - 1) * 32, (Height - 2 -MapHeightValues[i - 1]) * 32);
			TileMap[Height - 2 - MapHeightValues[i - 1]][i - 1].setSprite(tmp);
			TileMap[Height - 2 - MapHeightValues[i - 1]][i - 1].setType(4);
		}
	for (int i = 30; i < Width - 20; i++)
	{
		if (currentEnemy < countEnemys)
		{
			int isSpawnEnemy = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction)) % 100;
			if (isSpawnEnemy > 70)
			{
				hlth::Health health;
				health.setHealthPoints(100);
				Enemys[currentEnemy].setHealth(health);
				Enemys[currentEnemy].setCharacterHeight(50);
				Enemys[currentEnemy].setCharacterWidth(40);
				Enemys[currentEnemy].setDamageValue(10);
				Enemys[currentEnemy].Initialization(i * 32, (Height - MapHeightValues[i] - 3) * 32);
				currentEnemy++;
			}
		}
		else
			break;
	}
}

std::vector<Enemy> mp::Map::getEnemys()
{
	return Enemys;
}

void mp::Map::GenerateMap()
{
	
	srand(time(NULL));
	seed = 1 + std::rand() % 10000;
	countEnemys = 60 + abs((int)pg::PerlinNoise1D(seed,persistence,countNoiseFunction)) % 71;
	Enemys.resize(countEnemys);
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
	for (int i = 0; i < rndMapPoints[0]; i++)
		for (int j = MapHeightValues[i] - 1; j > 0; j--)
		{
			tmp.setPosition(i * 32, (Height - 1 - j) * 32);
			TileMap[Height - 1 - j][i].setSprite(tmp);
			TileMap[Height - 1 - j][i].setType(3);
		}
	for(int k = 1; k < countCaves; k++)
	{
		for (int i = rndMapPoints[k - 1] + CavesWidth; i < rndMapPoints[k]; i++)
			for (int j = MapHeightValues[i] - 1; j > 0; j--)
			{
				tmp.setPosition(i * 32, (Height - 1 - j) * 32);
				TileMap[Height - 1 - j][i].setSprite(tmp);
				TileMap[Height - 1 - j][i].setType(3);
			}

	}
	for (int i = rndMapPoints[countCaves - 1] + CavesWidth; i < Width; i++)
		for (int j = MapHeightValues[i] - 1; j > 0; j--)
		{
			tmp.setPosition(i * 32, (Height - 1 - j) * 32);
			TileMap[Height - 1 - j][i].setSprite(tmp);
			TileMap[Height - 1 - j][i].setType(3);
		}
	FillMap();
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
