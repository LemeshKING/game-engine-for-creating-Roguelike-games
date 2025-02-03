#include "Meadows.h"

void Meadows::FillMap()
{
	creatorGameObjects = std::make_unique<ThornsCreator>();
	for (int i = 3; i < Width; i++)
		if ((MapHeightValues[i - 3] == MapHeightValues[i]) && (MapHeightValues[i - 3] - MapHeightValues[i - 2] == 1) && (MapHeightValues[i] - MapHeightValues[i - 1] == 1))
		{
			IntVector tmp{ (i - 2) * 32 , (int)(Height - 2 - MapHeightValues[i - 2]) * 32 - 4 };
			TileMap[Height - 1 - MapHeightValues[i - 2]][i - 2].Object = creatorGameObjects->factoryMethod(tmp);


			tmp[0] = (i - 1) * 32;
			tmp[1] = (Height - 2 - MapHeightValues[i - 1]) * 32 - 4;
			TileMap[Height - 1 - MapHeightValues[i - 1]][i - 1].Object = creatorGameObjects->factoryMethod(tmp);

		}
	for (int i = 4; i < Width; i++)
		if ((MapHeightValues[i - 4] == MapHeightValues[i]) && MapHeightValues[i - 4] - MapHeightValues[i - 3] == 1 && MapHeightValues[i] - MapHeightValues[i - 1] == 1)
		{
			IntVector tmp{ (i - 3) * 32 , (int)(Height - 2 - MapHeightValues[i - 3]) * 32 - 4 };
			TileMap[Height - 1 - MapHeightValues[i - 3]][i - 3].Object = creatorGameObjects->factoryMethod(tmp);



			tmp[0] = (i - 2) * 32;
			tmp[1] = (Height - 2 - MapHeightValues[i - 2]) * 32 - 4;
			TileMap[Height - 1 - MapHeightValues[i - 2]][i - 2].Object = creatorGameObjects->factoryMethod(tmp);


			tmp[0] = (i - 1) * 32;
			tmp[1] = (Height - 2 - MapHeightValues[i - 1]) * 32 - 4;
			TileMap[Height - 1 - MapHeightValues[i - 1]][i - 1].Object = creatorGameObjects->factoryMethod(tmp);

		}
	for (int i = 30; i < Width - 20; i++)
	{
		if (currentEnemy < countEnemys)
		{
			int isSpawnEnemy = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction)) % 100;
			if (isSpawnEnemy > 70)
			{
				int TypeEnemy = abs((int)pg::PerlinNoise1D(i * seed + currentEnemy, persistence, countNoiseFunction)) % 100;

				if (TypeEnemy < 70)
					creatorEnemys = std::make_unique<ZombieCreator>();
				else
					creatorEnemys = std::make_unique</*WizardCreator*/ZombieCreator>();

				SPtrEnemy enemy = creatorEnemys->factoryMethod();
				enemy->Initialization(i * 32, (Height - MapHeightValues[i] - 3) * 32);
				TileMap[Height - MapHeightValues[i] - 3][i].enemysOnTile.push_back(enemy);
				currentEnemy++;
				
			}
		}
		else
			break;
	}
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			TypeOfTiles[i][j] = TileMap[i][j].getTileType();
}

void Meadows::GenerateLocation()
{
	srand(time(NULL));
	seed = 1 + std::rand() % 10000;
	countEnemys = 60 + abs((int)pg::PerlinNoise1D(seed, persistence, countNoiseFunction)) % 71;
	_Enemys.resize(countEnemys);
	TileMap.resize(Height);
	TypeOfTiles.resize(Height);
	sf::Sprite tmp;
	if (!texture.loadFromFile("../src/Map/tileset.png"))
		texture.loadFromFile("../../src/Map/tileset.png");
	tmp.setTexture(texture);
	tmp.setTextureRect(sf::IntRect(96, 0, 32, 32));
	for (auto& i : TypeOfTiles)
		i.resize(Width);
	for (auto& i : TileMap)
		i.resize(Width);
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
		{
			tmp.setPosition(j * 32, i * 32);
			TileMap[i][j].setSprite(tmp);
		}
	MapHeightValues.resize(Width);
	for (int i = 0; i < Width; i++)
		MapHeightValues[i] = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction)) % Height;
	smoothMap();
	tmp.setTextureRect(sf::IntRect(0, 0, 32, 32));
	for (int j = 0; j < Width; j++)
	{
		tmp.setPosition(j * 32, (Height - 1 - MapHeightValues[j]) * 32);
		TileMap[Height - 1 - MapHeightValues[j]][j].setSprite(tmp);
		TileMap[Height - 1 - MapHeightValues[j]][j].setType(1);
	}
	GenerateCaves();
	tmp.setTextureRect(sf::IntRect(32, 0, 32, 32));
	for (int i = 0; i < rndMapPoints[0]; i++)
		for (int j = MapHeightValues[i] - 1; j > 0; j--)
		{
			tmp.setPosition(i * 32, (Height - 1 - j) * 32);
			TileMap[Height - 1 - j][i].setSprite(tmp);
			TileMap[Height - 1 - j][i].setType(3);
		}
	for (int k = 1; k < countCaves; k++)
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
	for (int i = 0; i < Height; i++)
	{
		TileMap[i][0].setType(1);
		TileMap[i][Width - 1].setType(1);
	}
	FillMap();
}

void Meadows::smoothMap()
{
	for (auto& i : MapHeightValues)
		if (i >= Height - 3)
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

void Meadows::GenerateCaves()
{
	CavesWidth = 50;
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
		if (checkGeneration <= 0)
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




	for (int k = 0; k < countCaves; k++)
	{
		std::vector<int> CavesHeight(CavesWidth);
		CavesHeight[0] = MapHeightValues[rndMapPoints[k]];
		for (int i = rndMapPoints[k] + 1; i < rndMapPoints[k] + CavesWidth; i++)
			CavesHeight[i - rndMapPoints[k]] = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction) % (CavesHeight[0] - 6));
		SmoothCaves(CavesHeight);
		sf::Sprite tmp;
		tmp.setTexture(texture);
		tmp.setTextureRect(sf::IntRect(64, 0, 32, 32));

		for (int i = rndMapPoints[k]; i < rndMapPoints[k] + CavesWidth; i++)
		{
			tmp.setPosition(i * 32, (Height - 1 - CavesHeight[i - rndMapPoints[k]]) * 32);
			TileMap[Height - 1 - CavesHeight[i - rndMapPoints[k]]][i].setSprite(tmp);
			TileMap[Height - 1 - CavesHeight[i - rndMapPoints[k]]][i].setType(1);
		}

		for (int i = MapHeightValues[rndMapPoints[k] + CavesWidth - 1] - 1; i > 0; i--)
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
		tmp.setTextureRect(sf::IntRect(96, 0, 32, 32));
		for (int i = rndMapPoints[k] + 1; i < rndMapPoints[k] + 5; i++)
		{
			tmp.setPosition(i * 32, (Height - 1 - MapHeightValues[i]) * 32);
			TileMap[Height - 1 - MapHeightValues[i]][i].setSprite(tmp);
			TileMap[Height - 1 - MapHeightValues[i]][i].setType(0);
		}
		//for (int i = 10; i < CavesWidth - 5; i++)
		//{
		//	if (currentEnemy < countEnemys)
		//	{
		//		int isSpawnEnemy = abs((int)pg::PerlinNoise1D(i * seed, persistence, countNoiseFunction)) % 100;
		//		if (isSpawnEnemy > 70)
		//		{
		//			int TypeEnemy = abs((int)pg::PerlinNoise1D(i * seed * currentEnemy, persistence, countNoiseFunction)) % 100;

		//			if (TypeEnemy < 70)
		//				creatorEnemys = std::make_unique<ZombieCreator>();
		//			/*else
		//				creatorEnemys = std::make_unique<WizardCreator>();*/
		//			SPtrEnemy enemy = creatorEnemys->factoryMethod();
		//			enemy->Initialization((i + rndMapPoints[k]) * 32, (Height - CavesHeight[i] - 3) * 32);
		//			TileMap[Height - CavesHeight[i] - 3][i].enemysOnTile.push_back(enemy);
		//			currentEnemy++;
		//		}
		//	}
		//	else
		//		break;
		//}
		sf::Sprite tmp1;
		creatorGameObjects = std::make_unique<TeleportCreator>();
		IntVector tmp2{ rndMapPoints[k] * 32 ,(int)(Height - CavesHeight[0] - 2) * 32, (rndMapPoints[k] + CavesWidth - 3) * 32, (int)(Height - CavesHeight[CavesWidth - 2] - 2) * 32 - 64 };
		TileMap[Height - CavesHeight[CavesWidth - 3] - 1][rndMapPoints[k] + CavesWidth - 3].Object = creatorGameObjects->factoryMethod(tmp2);
		TileMap[Height - CavesHeight[CavesWidth - 5] - 1][rndMapPoints[k] + CavesWidth - 5].Weapon = std::make_shared <sword>();
		tmp1 = TileMap[Height - CavesHeight[CavesWidth - 5] - 1][rndMapPoints[k] + CavesWidth - 5].Weapon->getSprite();
		tmp1.setPosition((rndMapPoints[k] + CavesWidth - 5) * 32, (Height - CavesHeight[CavesWidth - 5] - 2) * 32);
		tmp1.setRotation(45);

		TileMap[Height - CavesHeight[CavesWidth - 5] - 1][rndMapPoints[k] + CavesWidth - 5].Weapon->setDamageValue(55);
		TileMap[Height - CavesHeight[CavesWidth - 5] - 1][rndMapPoints[k] + CavesWidth - 5].Weapon->setRect(tmp1.getGlobalBounds());
		TileMap[Height - CavesHeight[CavesWidth - 5] - 1][rndMapPoints[k] + CavesWidth - 5].Weapon->setSrite(tmp1);


	}

}

void Meadows::SmoothCaves(IntVector& Cave)
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
