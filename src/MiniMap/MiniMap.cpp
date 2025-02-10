#include "MiniMap.h"

void MiniMap::drawMiniMapTexture(sf::RenderTexture& miniMapTexture, const std::vector<std::vector<int>>& tileMap)
{
   miniMapTexture.create(tileMap[0].size() * miniMapTileSize, tileMap.size() * miniMapTileSize);
	miniMapTexture.clear(sf::Color::Transparent);
	sf::RectangleShape tile(sf::Vector2f(miniMapTileSize, miniMapTileSize));
	for (int i = 0; i < tileMap.size(); i++)
		for (int j = 0; j < tileMap[i].size(); j++)
		{
			if (tileMap[i][j] == 1 ||tileMap[i][j] == 3)
				tile.setFillColor(sf::Color(0, 0, 0, 250));
			else
				tile.setFillColor(sf::Color(255, 255, 255, 150));
			tile.setPosition(j * miniMapTileSize, i * miniMapTileSize);
			miniMapTexture.draw(tile);
		}


//	miniMapTexture.draw(playerOnMiniMap);
	miniMapTexture.display();
	texture = miniMapTexture.getTexture();
	sprite.setTexture(texture);
	sprite.scale(0.07, 0.14);

}


sf::Sprite MiniMap::getSprite()
{
	return sprite;
}


void MiniMap::setPosition(float x, float y)
{
	sprite.setPosition(x - 448, y - 260);
}
