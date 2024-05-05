#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

class Animation
{
private:
   std::vector<sf::IntRect> frames, flipFrames;
   sf::Sprite sprite;
   float speed;
   float currentFrame = 0;
   bool flip = false;
public:
   void setTexture(sf::Texture &_texture);
   void setAnimationFrames(int &count, int &x, int &y, int &width, int &height);
   void setAnimationSpeed(float &_speed);
   void ChangeFrame(float time);
   void FlipAnimation(bool isFlip);
   sf::Sprite getSprite();
   void setPosition(int x, int y);
   int getFrame();
   void setFrame(int frame);
};