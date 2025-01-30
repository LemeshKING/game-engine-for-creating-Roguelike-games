#pragma once
#include "../player/player.h"
#include "../enemy/enemy.h"
#include "../LocationCreator/LocationCreator.h"
#include "../sword/sword.h"
#include "../HealthBar/HealthBar.h"

#include <iostream>

typedef std::unique_ptr<LocationCreator> UPtrLC;

class Game
{
private:
   int w = 1920;
   int h = 1080;
   int mouseX = w / 2 + 64;
   int mouseY = h / 2;
   std::shared_ptr<HealthBar> healthBar;
   UPtrMap location;
   UPtrEnemyVector Enemys;
   Player pl;
public:
   Game();
   void TestingProceduralGeneration(sf::RenderWindow& window);
   void TestingPlayerMove(sf::RenderWindow& window);
   void TestingInterectionWithEnemy(sf::RenderWindow& window);
   void Run(sf::RenderWindow &window);
   void Pause();
   void Menu();
   void Initialization();

};

