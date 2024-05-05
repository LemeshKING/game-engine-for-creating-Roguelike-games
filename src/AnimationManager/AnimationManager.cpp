#include "AnimationManager.h"

void ar::AnimationManager::CreateAnimation(std::string name, int x, int y, int width, int height, int count, float speed)
{
   AnimationList[name] = Animation();
   AnimationList[name].setTexture(texture);
   AnimationList[name].setAnimationFrames(count, x, y, width, height);
   AnimationList[name].setAnimationSpeed(speed);
   currentAnimation = name;
}

Animation ar::AnimationManager::getAnimation()
{
   return AnimationList[currentAnimation];
}

void ar::AnimationManager::setTexture(sf::Texture& _texture)
{
   texture = _texture;
}

 void ar::AnimationManager::flipAnimation(bool isFlip)
{
   AnimationList[currentAnimation].FlipAnimation(isFlip);
}

void ar::AnimationManager::tick(float time)
{

   AnimationList[currentAnimation].ChangeFrame(time);
  
}

void ar::AnimationManager::setPosition(int x, int y)
{
   AnimationList[currentAnimation].setPosition(x,y);
}

void ar::AnimationManager::setAnimation(std::string name)
{
   currentAnimation = name;
}

void ar::AnimationManager::setFrame(int frame)
{
   AnimationList[currentAnimation].setFrame(frame);
}




