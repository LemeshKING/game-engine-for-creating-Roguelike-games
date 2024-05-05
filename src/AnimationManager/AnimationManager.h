#pragma once
#include "../Animation/Animation.h"
#include<map>
#include <string>
namespace ar
{
   class AnimationManager
   {
   private:
      sf::Texture texture;
      std::string currentAnimation;
      std::map<std::string,Animation> AnimationList;

   public:
      void CreateAnimation(std::string name, int x, int y, int width, int height, int count, float speed);
      Animation getAnimation();
      void setTexture(sf::Texture &_texture);
      void flipAnimation(bool isFlip);
      void tick(float time);
      void setPosition(int x, int y);
      void setAnimation(std::string name);
      void setFrame(int frame);

   };
}