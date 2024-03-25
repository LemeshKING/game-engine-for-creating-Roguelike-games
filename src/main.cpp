#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "proceduralgeneration/ProceduralGeneration.h"

const int Height = 70;
const int Width = 1000;

std::vector<std::vector<int>> Tilemap(Height,std::vector<int>(Width));



int main()
{
	sf::View view;
	view.reset(sf::FloatRect(0, 0,1920,1080));
	int w = 1920;
	int h = 1080;
	int mouseX = w / 2 + 64;
	int mouseY = h / 2;
	srand(time(NULL));
   int seed = 1 + std::rand() % 1000;
	//float mouseSensitivity = 3.0f;
	//float speed = 0.1f;
	//bool mouseHidden = true;
	//bool wasdUD[6] = { false, false, false, false, false, false };
	//sf::Vector3f pos = sf::Vector3f(-5.0f, 0.0f, 0.0f);
	//sf::Clock clock;
	//int framesStill = 1;
	sf::RectangleShape rectangle(sf::Vector2f(32,32));
	
	sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	//window.setMouseCursorVisible(false);

	//sf::RenderTexture emptyTexture;
	//emptyTexture.create(w,h);
	//sf::Sprite emptySprite = sf::Sprite(emptyTexture.getTexture());
	//
	//sf::Shader shader;
	//shader.loadFromFile("Shaders.frag", sf::Shader::Fragment);
	//shader.setUniform("u_resolution", sf::Vector2f(w, h));
   
	std::vector<int> tmp(Width);
	for (int i = 0; i < Width; i++)
		tmp[i] = pg::PerlinNoise1D(i * seed, 5, 10);
	
	for (auto &i : tmp)
	{
		if(i < 0)
			i = 1;
		else if (i >= Height-3)
			i = Height - 6;
	}
	for (int i = 1; i < Width; i++)
	{
		if(tmp[i] - tmp[i-1] > 1)
			tmp[i] -= tmp[i] - tmp[i - 1] - 1;
		else if (tmp[i] - tmp[i - 1] < -1)
			tmp[i] += tmp[i - 1] - tmp[i] - 1;
	}
   for(int i = 2; i < Width; i++)
		if(tmp[i-2] == tmp[i] && abs(tmp[i - 1] - tmp[i]) == 1)
			tmp[i-1] = tmp[i];
	for(int j = 0; j < Width; j++)
		Tilemap[Height - 1 - tmp[j]][j] = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//	else if (event.type == sf::Event::MouseMoved)
		//	{
		//		if (mouseHidden)
		//		{
		//			int mx = event.mouseMove.x - w / 2;
		//			int my = event.mouseMove.y - h / 2;
		//			mouseX += mx;
		//			mouseY += my;
		//			sf::Mouse::setPosition(sf::Vector2i(w / 2, h / 2), window);

		//		}
		//	}
		//	else if (event.type == sf::Event::MouseButtonPressed)
		//	{
		//		
		//		window.setMouseCursorVisible(false);
		//		mouseHidden = true;
		//	}
		//	else if (event.type == sf::Event::KeyPressed)
		//	{
		//		if (event.key.code == sf::Keyboard::Escape)
		//		{
		//			window.setMouseCursorVisible(true);
		//			mouseHidden = false;
		//		}
		//		else if (event.key.code == sf::Keyboard::W) wasdUD[0] = true;
		//		else if (event.key.code == sf::Keyboard::A) wasdUD[1] = true;
		//		else if (event.key.code == sf::Keyboard::S) wasdUD[2] = true;
		//		else if (event.key.code == sf::Keyboard::D) wasdUD[3] = true;
		//		else if (event.key.code == sf::Keyboard::Space) wasdUD[4] = true;
		//		else if (event.key.code == sf::Keyboard::LShift) wasdUD[5] = true;
		//	}
		//	else if (event.type == sf::Event::KeyReleased)
		//	{
		//		if(event.key.code == sf::Keyboard::W) wasdUD[0] = false;
		//		else if (event.key.code == sf::Keyboard::A) wasdUD[1] = false;
		//		else if (event.key.code == sf::Keyboard::S) wasdUD[2] = false;
		//		else if (event.key.code == sf::Keyboard::D) wasdUD[3] = false;
		//		else if (event.key.code == sf::Keyboard::Space) wasdUD[4] = false;
		//		else if (event.key.code == sf::Keyboard::LShift) wasdUD[5] = false;

		//	}
		//}
		//if (mouseHidden)
		//{
		//	sf::Vector3f dirTemp;
		//	sf::Vector3f dir = sf::Vector3f(0.0f, 0.0f, 0.0f);
		//	if(wasdUD[0]) dir = sf::Vector3f(-1.0f, 0.0f, 0.0f);
		//	else if (wasdUD[2]) dir = sf::Vector3f(1.0f, 0.0f, 0.0f);
		//	if(wasdUD[1]) dir += sf::Vector3f(0.0f, -1.0f, 0.0f);
		//	else if (wasdUD[3]) dir += sf::Vector3f(0.0f, 1.0f, 0.0f);


		//	float mx = ((float)mouseX / w - 0.5f) * mouseSensitivity;
		//	float my = ((float)mouseY / h - 0.5f) * mouseSensitivity;
		//	dirTemp.z = dir.z * cos(-my) - dir.x * sin(-my);
		//	dirTemp.x = dir.z * sin(-my) - dir.x * cos(-my);
		//	dirTemp.y = dir.y;
		//	dir.x = dirTemp.x * cos(mx) - dirTemp.y * sin(mx);
		//	dir.y = dirTemp.x * sin(mx) + dirTemp.y * cos(mx);
		//	dir.z = dirTemp.z;
		//	pos += dir * speed;
		//	if (wasdUD[4]) pos.z -= 0.1;
		//	else if (wasdUD[5]) pos.z += 0.1;
		//	shader.setUniform("u_pos", pos);
		//	shader.setUniform("u_mouse",sf::Vector2f(mx,my));
		//	window.draw(emptySprite,&shader);
		//	
		//}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(mouseX < (Width - 32) * 32)
					mouseX += 64;
				view.setCenter(mouseX,mouseY);
			}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if(mouseX > 32 * 32)
				mouseX -= 64;
			view.setCenter(mouseX, mouseY);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mouseY -= 64;
			view.setCenter(mouseX, mouseY);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mouseY += 64;
			view.setCenter(mouseX, mouseY);

		}
		for(int i = 0; i < Height; i++)
			for(int j = mouseX / 32 - 32; j < mouseX / 32 + 32; j++)
			{
				if(Tilemap[i][j] == 1)
					rectangle.setFillColor(sf::Color::Black);
				if(Tilemap[i][j] == 0)
					rectangle.setFillColor(sf::Color::White);
				rectangle.setPosition(j * 32, i * 32);
				window.draw(rectangle);
			}
		window.display();
		window.setView(view);
		window.clear(sf::Color::White);
      }
	
	return 0;
}