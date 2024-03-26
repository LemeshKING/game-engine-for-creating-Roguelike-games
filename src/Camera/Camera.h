#pragma once
#include "SFML/Graphics.hpp"
class Camera
{
   int windowHeight;
   int windowWidth;
   sf::View camera;
   int centerX = 0, centerY = 0;
 public:
   void setCenterX(int _centerX);
   void setCenterY(int _centerY);
   int getCenterX();
   int getCenterY();
   void setCenter();
   void setWindowHeight(int _windowHeight);
   void setWindowWidth(int _windowWidth);
   sf::View getView();
   void setView(sf::View _view);
};