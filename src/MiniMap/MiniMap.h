#pragma once
#include<SFML/Graphics.hpp>

class MiniMap
{
 private:
   unsigned char miniMapTileSize = 10;
   sf::Sprite sprite;

   sf::Texture texture;
 public:
   void drawMiniMapTexture(sf::RenderTexture &miniMapTexteru, const std::vector<std::vector<int>> &tileMap);

   sf::Sprite getSprite();

   void setPosition(float x, float y);
};