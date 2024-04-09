#include "Camera.h"

void Camera::setCenterX(int _centerX)
{
   if(_centerX > viewMode.x / 2)
      centerX = _centerX;
   else
      centerX = viewMode.x / 2;
}

void Camera::setCenterY(int _centerY)
{
   if(_centerY > viewMode.y / 2 + 32)
      centerY = _centerY;
   else
      centerY = viewMode.y / 2 + 32;
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

void Camera::setViewMode(sf::Vector2u _viewMode)
{
   viewMode = _viewMode;
   camera.reset(sf::FloatRect(windowWidth,windowHeight, _viewMode.x,_viewMode.y));
}

sf::Vector2u Camera::getViewMode()
{
   return viewMode;
}
