#include "player.h"

Player::Player()
{
}

void Player::Initialization(int x, int y)
{
   rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   rectangle.setSize(sf::Vector2f(rect.width, rect.height));
   rectangle.setFillColor(sf::Color::Green);
   rectangle.setPosition(rect.left,rect.top);
   camera.setCenterX(rect.left);
   camera.setCenterY(rect.top);
}

void Player::update(const float& time, const std::vector<std::vector<int>>& location)
{
   dx *= direction;
   rect.left += dx * time;
   CollisionX(location);
   if (!onGround) dy = dy + 0.005 * time;
   rect.top += dy * time;
   onGround = false;
   Weapon->update(rect.left + rect.width, rect.top);
   
   CollisionY(location);
   rectangle.setPosition(rect.left, rect.top);
   if(camera.getCenterX() > (location[0].size() - 17) * 32)
      camera.setCenterX((location[0].size() - 17) * 32);
   else if (rect.left < (location[0].size() - 17) * 32 && dx < 0)
      camera.setCenterX(rect.left);
   else if(camera.getCenterX() < (location[0].size() - 17) * 32)
      camera.setCenterX(rect.left);
   camera.setCenterY(rect.top);
   camera.setCenter();
   dx = 0;
}

void Player::setCamera(Camera &_camera)
{
   camera = _camera;
}

Camera Player::getCamera()
{
   return camera;
}

void Player::TakeDamage(int damageValue)
{
   health.TakeDamage(damageValue);
   if(health.getHealthPoints() == 0)
      Kill();
   dx = -1 * direction * 5;
   dy = -0.5;
   immunity = true;
      
}

bool Player::isImmunity()
{
   return immunity;
}

void Player::removeImmunity()
{
   immunity = false;
}

void Player::setWeapon(weapon *_weapon)
{
   Weapon = _weapon;
}

weapon* Player::getWeapon()
{
   return Weapon;
}



void Player::CollisionX(const std::vector<std::vector<int>>& location)
{
   for(int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for(int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if(location[i][j] == 1)
            if(dx > 0)
               rect .left = j * 32 - rect.width;
            else if (dx < 0)
               rect.left = j * 32 + 32;
            
}

void Player::CollisionY(const std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1)
            if (dy > 0)
            { 
               rect.top = i * 32 - rect.height; 
               dy = 0; 
               onGround = true;
            }
            else if (dy < 0)
            {
               rect.top = i * 32 + 32;
               dy = 0;
            }
}
