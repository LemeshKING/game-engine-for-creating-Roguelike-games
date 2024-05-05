#include "sword.h"

sword::sword()
{
   if (!texture.loadFromFile("../src/sword/sword.png"))
      texture.loadFromFile("../../src/sword/sword.png");
   sprite.setTexture(texture);
   sprite.setTextureRect(sf::IntRect(0, 0, 35, 10));
}

void sword::Attack()
{

}
