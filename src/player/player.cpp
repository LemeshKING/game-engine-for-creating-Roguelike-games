#include "player.h"

Player::Player()
{
}

void Player::Initialization(int x, int y)
{
   CharacterState = stay;
   physicalQ.m = 50;
   physicalQ.dy = -0.2;
   physicalQ.rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   camera.setCenterX(physicalQ.rect.left);
   camera.setCenterY(physicalQ.rect.top);
   if(!texture.loadFromFile("../src/player/player.png"))
      texture.loadFromFile("../../src/player/player.png");
   animation.setTexture(texture);
   animation.CreateAnimation("stay",0,0,characterWidth,characterHeight,4,0.006);
   animation.CreateAnimation("walk",0,50,characterWidth,characterHeight,4,0.012);
   animation.CreateAnimation("jump",0,100,characterWidth,characterHeight,4,0.018);
   animation.CreateAnimation("attack",0,150,characterWidth,characterHeight,5,0.022);
}

void Player::update(const float time, IntVectorVector& location)
{
   ChangeStateCharacter();
   if (CharacterState == stay) animation.setAnimation("stay");
   if (CharacterState == walk) animation.setAnimation("walk");
   if (CharacterState == jumping) animation.setAnimation("jump");
   if (CharacterState == attack) animation.setAnimation("attack");
   animation.flipAnimation(direction < 0);
   animation.tick(time);
   onGround = false;
   canMove = true;
   if(immunity && !dashing)
      immuneFrames++;
   if (immuneFrames > 144)
   {
      immuneFrames = 0;
      immunity = false;
   }
   if(dashing)
      dashFramers++;
   if(dashing && dashFramers < 65)
   {  
      physicalQ.dx = 0.4;
      BecomeImmune();
      dashColdown = 0;
      canMove = false;
   }
   if(dashFramers >= 65 && dashing)
      key["Dash"] = false;

   
   if (dashFramers > 100)
   {
      dashFramers = 0;
      dashing = false;
      removeImmunity();
   }
   dashColdown++;
   if(satDown)
   {
      physicalQ.rect.height = characterHeight / 1.35;
      canMove = false;
   }
   else 
      physicalQ.rect.height = characterHeight;

   raisingFrames++;
   physicalQ.dx *= direction;
   physicalQ.rect.left += physicalQ.dx * time;
   CollisionX(location);
   if (!onGround) physicalQ.dy = physicalQ.dy + 0.005 * time;
   if(dashing && dashFramers < 65) physicalQ.dy = 0;
   physicalQ.rect.top += physicalQ.dy * time;
   CollisionY(location);
   
   if(direction > 0)
   {
      sf::Sprite tmp = Weapon->getSprite();
      tmp.setTextureRect(sf::IntRect(0, 0, 35, 10));
      Weapon->setSrite(tmp);
      Weapon->update(physicalQ.rect.left + physicalQ.rect.width, physicalQ.rect.top);
   }
   else
   {
      sf::Sprite tmp = Weapon->getSprite();
      tmp.setTextureRect(sf::IntRect(35,0,-35,10));
      Weapon->setSrite(tmp);
      Weapon->update(physicalQ.rect.left - Weapon->getRect().width + 3, physicalQ.rect.top);
   }
   

   animation.setPosition(physicalQ.rect.left, physicalQ.rect.top);
   camera.setCenterX(physicalQ.rect.left);
   if(camera.getCenterX() > (location[0].size() - 17) * 32)
      camera.setCenterX((location[0].size() - 17) * 32);

   camera.setCenterY(physicalQ.rect.top);
   if(physicalQ.rect.top > (location.size() - 10) * 32)
      camera.setCenterY((location.size() - 10) * 32);
   camera.setCenter();
   
   physicalQ.dx = 0;
   key["L"] = key["R"] = key["Up"] = false;
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
   if(!immunity)
   {  
      health.TakeDamage(damageValue);
      Notify();
      if(health.getHealthPoints() == 0)
         Kill();
      physicalQ.dx = -1 * direction * 5;
      physicalQ.dy = -0.5;
      immunity = true;
   }
}

bool Player::isImmunity()
{
   return immunity;
}

void Player::removeImmunity()
{
   immunity = false;
}

void Player::setWeapon(SPtrWeapon &_weapon)
{
   Weapon = _weapon;
}

void Player::BecomeImmune()
{
   immunity = true;
}

SPtrWeapon Player::getWeapon()
{
   return Weapon;
}

void Player::Attach(SPtrObserver &observer)
{
   Observers.push_back(observer);
}

void Player::Detach(SPtrObserver &observer)
{
   Observers.remove(observer);
}

void Player::Notify()
{
   for(auto &i: Observers)
      i->HealthChange(health.getHealthPoints());
}

void Player::gainMoney(unsigned int& cost)
{
   wallet += cost;
}


void Player::ChangeStateCharacter()
{
   if (key["L"])
   {
      direction = -1;
      physicalQ.dx = 0.25;
      if(CharacterState == stay)
         CharacterState = walk;
   }
   if (key["R"])
   {
      direction = 1;
      physicalQ.dx = 0.25;
      if (CharacterState == stay)
         CharacterState = walk;
   }
   if (key["Up"])
   {
      if (CharacterState != attack)
         if (onGround)
         {
            physicalQ.dy = -0.65;
            CharacterState = jumping;
           
         }
      
   }
   if (key["Attack"])
   {
      CharacterState = attack;
   }
   if (key["Dash"])
   {
      if (CharacterState != attack)
      {
         CharacterState = walk;
         dashing = true;
      }
   }
   if (!(key["L"] || key["R"]))
   {
      physicalQ.dx = 0;
      if(CharacterState == walk && !dashing)
         CharacterState = stay;
   }
   if(!key["Up"])
      if(CharacterState == jumping && onGround)
         CharacterState = stay;
   if (!key["Attack"])
      if(CharacterState == attack)
         CharacterState = walk;
 
}



void Player::CollisionX(IntVectorVector& location)
{
   for(int i = physicalQ.rect.top / 32; i < (physicalQ.rect.top + physicalQ.rect.height) / 32; i++)
      for(int j = physicalQ.rect.left / 32; j < (physicalQ.rect.left + physicalQ.rect.width) / 32; j++)
         if(location[i][j] ==  1 || location[i][j] == 3)
            if(physicalQ.dx > 0)
               physicalQ.rect.left = j * 32 - physicalQ.rect.width;
            else if (physicalQ.dx < 0)
               physicalQ.rect.left = j * 32 + 32;
            
}

void Player::CollisionY(IntVectorVector& location)
{
   for (int i = physicalQ.rect.top / 32; i < (physicalQ.rect.top + physicalQ.rect.height) / 32; i++)
      for (int j = physicalQ.rect.left / 32; j < (physicalQ.rect.left + physicalQ.rect.width) / 32; j++)
         if (location[i][j] == 1  || location[i][j] == 3)
         { 
            if (physicalQ.dy > 0)
            { 
               physicalQ.rect.top = i * 32 - physicalQ.rect.height;
               physicalQ.dy = 0;
               onGround = true;
            }
            else if (physicalQ.dy < 0)
            {
               physicalQ.rect.top = i * 32 + 32;
               physicalQ.dy = 0;

            }
         }
        
}
