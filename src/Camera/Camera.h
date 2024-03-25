#pragma once
#include "SFML/Graphics.hpp"
class Camera
{
   sf::View camera;
   int centerX, centerY;
 public:
   void setCenterX(int _centerX);
   void setCenterY(int _centerY);
   int getCenterX();
   int getCenterY();

};