#include "Camera.h"

void Camera::setCenterX(int _centerX)
{
   if(_centerX > windowWidth / 2)
      centerX = _centerX;
   else
      centerX = windowWidth / 2;
}

void Camera::setCenterY(int _centerY)
{
   centerY = _centerY;
}

int Camera::getCenterX()
{
   return centerX;
}

int Camera::getCenterY()
{
   return centerY;
}

void Camera::setCenter()
{
   camera.setCenter(centerX,centerY);
}

void Camera::setWindowHeight(int _windowHeight)
{
   windowHeight = _windowHeight;
}

void Camera::setWindowWidth(int _windowWidth)
{
   windowWidth = _windowWidth;
}

sf::View Camera::getView()
{
   return camera;
}

void Camera::setView(sf::View _view)
{
   camera = _view;
}
