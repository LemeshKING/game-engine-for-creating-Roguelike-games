#include "../player/player.h"
#include "../enemy/enemy.h"
#include "../Map/map.h"
#include "../sword/sword.h"
#include "../HealthBar/HealthBar.h"

#include <iostream>
class Game
{
private:
   int w = 1920;
   int h = 1080;
   int mouseX = w / 2 + 64;
   int mouseY = h / 2;
   HealthBar healthBar;
   mp::Map location;
   std::vector<Enemy*> Enemys;
   Player pl;
public:
   Game();
   void Run(sf::RenderWindow &window);
   void Pause();
   void Menu();
   void Initialization();

};

