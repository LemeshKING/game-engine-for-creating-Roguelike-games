#include "Animation.h"

void Animation::setTexture(sf::Texture& _texture)
{
   sprite.setTexture(_texture);
}

void Animation::setAnimationFrames(int &count, int &x, int &y, int &width, int &height)
{
   frames.resize(count);
   flipFrames.resize(count);
   for (int i = 0; i < count; i++)
   {
      frames[i] = sf::IntRect(x + i * width, y, width, height);
      flipFrames[i] = sf::IntRect(x + i * width + width, y, -width, height);
   }
}

void Animation::setAnimationSpeed(float& _speed)
{
   speed = _speed;
}

void Animation::ChangeFrame(float time)
{
   currentFrame += speed * time;
   if(currentFrame > frames.size())
      currentFrame = 0;
   int i = currentFrame;
   sprite.setTextureRect(frames[i]);
   if(flip)
      sprite.setTextureRect(flipFrames[i]);
}

void Animation::FlipAnimation(bool isFlip)
{
   flip = isFlip;
}

sf::Sprite Animation::getSprite()
{
   return sprite;
}

void Animation::setPosition(int x, int y)
{
   sprite.setPosition(x,y);
}

int Animation::getFrame()
{
   return (int)currentFrame;
}

void Animation::setFrame(int frame)
{
   currentFrame = frame;
}
