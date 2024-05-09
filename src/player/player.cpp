#include "player.h"

Player::Player()
{
}

void Player::Initialization(int x, int y)
{
   CharacterState = stay;
   rect = sf::FloatRect(x, y, characterWidth, characterHeight);
   rectangle.setSize(sf::Vector2f(rect.width, rect.height));
   rectangle.setFillColor(sf::Color::Green);
   rectangle.setPosition(rect.left,rect.top);
   camera.setCenterX(rect.left);
   camera.setCenterY(rect.top);
   if(!texture.loadFromFile("../src/player/player.png"))
      texture.loadFromFile("../../src/player/player.png");
   animation.setTexture(texture);
   animation.CreateAnimation("stay",0,0,characterWidth,characterHeight,4,0.006);
   animation.CreateAnimation("walk",0,50,characterWidth,characterHeight,4,0.012);
   animation.CreateAnimation("jump",0,100,characterWidth,characterHeight,4,0.018);
   animation.CreateAnimation("attack",0,150,characterWidth,characterHeight,5,0.022);
}

void Player::update(const float time, std::vector<std::vector<int>>& location)
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

      dx = 0.4;
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
      rect.height = characterHeight / 1.35;
      canMove = false;
   }
   else 
      rect.height = characterHeight;

   
   dx *= direction;
   rect.left += dx * time;
   CollisionX(location);
   if (!onGround) dy = dy + 0.005 * time;
   if(dashing && dashFramers < 65) dy = 0;
   rect.top += dy * time;
   CollisionY(location);
   
   if(direction > 0)
   {
      sf::Sprite tmp = Weapon->getSprite();
      tmp.setTextureRect(sf::IntRect(0, 0, 35, 10));
      Weapon->setSrite(tmp);
      Weapon->update(rect.left + rect.width, rect.top);
   }
   else
   {
      sf::Sprite tmp = Weapon->getSprite();
      tmp.setTextureRect(sf::IntRect(35,0,-35,10));
      Weapon->setSrite(tmp);
      Weapon->update(rect.left - Weapon->getRect().width + 3, rect.top);
   }
   
   rectangle.setSize(sf::Vector2f(rect.width,rect.height));
   rectangle.setPosition(rect.left, rect.top);
   animation.setPosition(rect.left,rect.top);
   camera.setCenterX(rect.left);
   if(camera.getCenterX() > (location[0].size() - 17) * 32)
      camera.setCenterX((location[0].size() - 17) * 32);

   camera.setCenterY(rect.top);
   if(rect.top > (location.size() - 10) * 32)
      camera.setCenterY((location.size() - 10) * 32);
   camera.setCenter();
   
   dx = 0;
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
      if(health.getHealthPoints() == 0)
         Kill();
      dx = -1 * direction * 5;
      dy = -0.5;
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

void Player::setWeapon(weapon *_weapon)
{
   Weapon = _weapon;
}

void Player::BecomeImmune()
{
   immunity = true;
}

weapon* Player::getWeapon()
{
   return Weapon;
}

void Player::ChangeStateCharacter()
{
   if (key["L"])
   {
      direction = -1;
      dx = 0.25;
      if(CharacterState == stay)
         CharacterState = walk;
   }
   if (key["R"])
   {
      direction = 1;
      dx = 0.25;
      if (CharacterState == stay)
         CharacterState = walk;
   }
   if (key["Up"])
   {
      if (CharacterState != attack)
         if (onGround)
         {
            dy = -0.65;
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
      dx = 0;
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



void Player::CollisionX(std::vector<std::vector<int>>& location)
{
   for(int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for(int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if(location[i][j] ==  1 || location[i][j] == 3)
            if(dx > 0)
               rect .left = j * 32 - rect.width;
            else if (dx < 0)
               rect.left = j * 32 + 32;
            
}

void Player::CollisionY(std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1  || location[i][j] == 3)
         { 
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
         else if (location[i][j] == 4)
         {
            if(!immunity)
               TakeDamage(health.getHealthPoints());
                
               
         }
}
