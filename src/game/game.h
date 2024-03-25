#include "../player/player.h"
#include "../enemy/enemy.h"
#include "../Map/map.h"
class Game
{
private:
   mp::Map location;
   std::vector<Enemy> Enemys;
   Player Player;
public:
   void Run();
   void Pause();
   void Menu();
   void Initialization();

};

