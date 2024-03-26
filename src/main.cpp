//#include "game/game.h"
//#include <omp.h>
//
//
//const int Height = 50;
//const int Width = 100;
//
//
//int main()
//{
//	int w = 1920;
//	int h = 1080;
//	int mouseX = w / 2 + 64;
//	int mouseY = h / 2;
//	mp::Map location;
//	//std::vector<Enemy> Enemys;
//	//Player Player;
//	//location.setHeight(Height);
//	//location.setWidth(Width);
//	//location.setPersistence(5);
//	//location.setCountNoiseFunction(8);
//	//location.GenerateMap();
//	//Player.Initialization(10 * 32, 0);
//	//Player.location = location.TileMap;
//	sf::View view;
//	view.reset(sf::FloatRect(0, 0, 1920, 1080));
//	sf::RectangleShape rectangle(sf::Vector2f(32, 32));
//	//sf::RectangleShape rectangle2(sf::Vector2f(400, 500));
//	//rectangle2.setFillColor(sf::Color::Green);
//	//rectangle2.setPosition(w / 2 + 64, h / 2);
//	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ray tracing", sf::Style::Fullscreen);
//	int frames = 0;
//
//	
//	while (window.isOpen())
//	{	
//		sf::Clock clock;
//		std::cout << clock.getElapsedTime().asMicroseconds() << std::endl;
//		float time = clock.getElapsedTime().asMicroseconds();
//		std::cout << "Time: "<< time << std::endl;
//		clock.restart();
//		time/=800;
//
//
//		/*float fps = 1.f / elapsed.asSeconds();
//		std::cout << "FPS: " << fps << std::endl;
//		frames++;*/
//		
//
//		/*if (frames % 100 == 0)
//			std::cout << "Average FPS over the last 100 frames: " << frames / clock.getElapsedTime().asSeconds() << std::endl;*/
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//		/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//			{
//				Player.dx = 0.5;
//			}
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//			{
//				Player.dx = -0.5;
//			}
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//				if (Player.onGround)
//					{
//						Player.dy = -2.5;
//						Player.onGround = false;
//					}*/
//			
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//			{
//				if (mouseX < (Width - 32) * 32)
//					mouseX += 64;
//				view.setCenter(mouseX, mouseY);
//			}
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//			{
//				if (mouseX > 32 * 32)
//					mouseX -= 64;
//				view.setCenter(mouseX, mouseY);
//
//			}
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//			{
//				mouseY -= 64;
//				view.setCenter(mouseX, mouseY);
//
//			}
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//			{
//				mouseY += 64;
//				view.setCenter(mouseX, mouseY);
//
//			}
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//				window.close();
//			
//		
//			//Player.update(time);
//			window.clear(sf::Color::White);
//			for (int i = 0; i < Height; i++)
//				for (int j = mouseX / 32 - 32; j < mouseX / 32 + 32; j++)
//				{
//					if (location.TileMap[i][j] == 1)
//						rectangle.setFillColor(sf::Color::Black);
//					if (location.TileMap[i][j] == 0)
//						rectangle.setFillColor(sf::Color::White);
//					rectangle.setPosition(j * 32, i * 32);
//					window.draw(rectangle);
//				}
//			
//			//window.draw(Player.rectangle);
//			window.display();
//
//			window.setView(view);
//
//		}
//	}
//
//	
//		//	else if (event.type == sf::Event::MouseMoved)
//		//	{
//		//		if (mouseHidden)
//		//		{
//		//			int mx = event.mouseMove.x - w / 2;
//		//			int my = event.mouseMove.y - h / 2;
//		//			mouseX += mx;
//		//			mouseY += my;
//		//			sf::Mouse::setPosition(sf::Vector2i(w / 2, h / 2), window);
//
//		//		}
//		//	}
//		//	else if (event.type == sf::Event::MouseButtonPressed)
//		//	{
//		//		
//		//		window.setMouseCursorVisible(false);
//		//		mouseHidden = true;
//		//	}
//		//	else if (event.type == sf::Event::KeyPressed)
//		//	{
//		//		if (event.key.code == sf::Keyboard::Escape)
//		//		{
//		//			window.setMouseCursorVisible(true);
//		//			mouseHidden = false;
//		//		}
//		//		else if (event.key.code == sf::Keyboard::W) wasdUD[0] = true;
//		//		else if (event.key.code == sf::Keyboard::A) wasdUD[1] = true;
//		//		else if (event.key.code == sf::Keyboard::S) wasdUD[2] = true;
//		//		else if (event.key.code == sf::Keyboard::D) wasdUD[3] = true;
//		//		else if (event.key.code == sf::Keyboard::Space) wasdUD[4] = true;
//		//		else if (event.key.code == sf::Keyboard::LShift) wasdUD[5] = true;
//		//	}
//		//	else if (event.type == sf::Event::KeyReleased)
//		//	{
//		//		if(event.key.code == sf::Keyboard::W) wasdUD[0] = false;
//		//		else if (event.key.code == sf::Keyboard::A) wasdUD[1] = false;
//		//		else if (event.key.code == sf::Keyboard::S) wasdUD[2] = false;
//		//		else if (event.key.code == sf::Keyboard::D) wasdUD[3] = false;
//		//		else if (event.key.code == sf::Keyboard::Space) wasdUD[4] = false;
//		//		else if (event.key.code == sf::Keyboard::LShift) wasdUD[5] = false;
//
//		//	}
//		//}
//		//if (mouseHidden)
//		//{
//		//	sf::Vector3f dirTemp;
//		//	sf::Vector3f dir = sf::Vector3f(0.0f, 0.0f, 0.0f);
//		//	if(wasdUD[0]) dir = sf::Vector3f(-1.0f, 0.0f, 0.0f);
//		//	else if (wasdUD[2]) dir = sf::Vector3f(1.0f, 0.0f, 0.0f);
//		//	if(wasdUD[1]) dir += sf::Vector3f(0.0f, -1.0f, 0.0f);
//		//	else if (wasdUD[3]) dir += sf::Vector3f(0.0f, 1.0f, 0.0f);
//
//
//		//	float mx = ((float)mouseX / w - 0.5f) * mouseSensitivity;
//		//	float my = ((float)mouseY / h - 0.5f) * mouseSensitivity;
//		//	dirTemp.z = dir.z * cos(-my) - dir.x * sin(-my);
//		//	dirTemp.x = dir.z * sin(-my) - dir.x * cos(-my);
//		//	dirTemp.y = dir.y;
//		//	dir.x = dirTemp.x * cos(mx) - dirTemp.y * sin(mx);
//		//	dir.y = dirTemp.x * sin(mx) + dirTemp.y * cos(mx);
//		//	dir.z = dirTemp.z;
//		//	pos += dir * speed;
//		//	if (wasdUD[4]) pos.z -= 0.1;
//		//	else if (wasdUD[5]) pos.z += 0.1;
//		//	shader.setUniform("u_pos", pos);
//		//	shader.setUniform("u_mouse",sf::Vector2f(mx,my));
//		//	window.draw(emptySprite,&shader);
//		//	
//		//}
//		}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "proceduralgeneration/ProceduralGeneration.h"
#include "enemy/enemy.h"
#include "player/player.h"
#include "Map/map.h"
#include "game/game.h"


const int Height = 70;
const int Width = 1000;

std::vector<std::vector<int>> Tilemap(Height, std::vector<int>(Width));



int main()
{	
	Game game;
	game.Initialization();
	mp::Map location;
	location.setHeight(Height);
	location.setWidth(Width);
	location.setPersistence(5);
	location.setCountNoiseFunction(10);
	location.GenerateMap();
	Player pl;
	pl.Initialization(320, 0);
	
	Enemy en;

	//sf::View view;
	//view.reset(sf::FloatRect(0, 0, 1920, 1080));
	//int w = 1920;
	//int h = 1080;
	//int mouseX = w / 2 + 64;
	//int mouseY = h / 2;
	//srand(time(NULL));
	//int seed = 1 + std::rand() % 1000;
	////float mouseSensitivity = 3.0f;
	////float speed = 0.1f;
	////bool mouseHidden = true;
	////bool wasdUD[6] = { false, false, false, false, false, false };
	////sf::Vector3f pos = sf::Vector3f(-5.0f, 0.0f, 0.0f);
	////sf::Clock clock;
	////int framesStill = 1;
	//sf::RectangleShape rectangle(sf::Vector2f(32, 32));

	//sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Fullscreen);
	//window.setFramerateLimit(60);
	////window.setMouseCursorVisible(false);

	////sf::RenderTexture emptyTexture;
	////emptyTexture.create(w,h);
	////sf::Sprite emptySprite = sf::Sprite(emptyTexture.getTexture());
	////
	////sf::Shader shader;
	////shader.loadFromFile("Shaders.frag", sf::Shader::Fragment);
	////shader.setUniform("u_resolution", sf::Vector2f(w, h));

	//std::vector<int> tmp(Width);
	//for (int i = 0; i < Width; i++)
	//	tmp[i] = pg::PerlinNoise1D(i * seed, 5, 10);

	//for (auto& i : tmp)
	//{
	//	if (i < 0)
	//		i = 1;
	//	else if (i >= Height - 3)
	//		i = Height - 6;
	//}
	//for (int i = 1; i < Width; i++)
	//{
	//	if (tmp[i] - tmp[i - 1] > 1)
	//		tmp[i] -= tmp[i] - tmp[i - 1] - 1;
	//	else if (tmp[i] - tmp[i - 1] < -1)
	//		tmp[i] += tmp[i - 1] - tmp[i] - 1;
	//}
	//for (int i = 2; i < Width; i++)
	//	if (tmp[i - 2] == tmp[i] && abs(tmp[i - 1] - tmp[i]) == 1)
	//		tmp[i - 1] = tmp[i];
	//for (int j = 0; j < Width; j++)
	//	Tilemap[Height - 1 - tmp[j]][j] = 1;
	//sf::Clock clock;
	//while (window.isOpen())
	//{
	//	float time = clock.getElapsedTime().asMicroseconds();
	//	time /= 800;
	//	clock.restart();
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//		{
	//			window.close();
	//		}
	//	}
	//	//	else if (event.type == sf::Event::MouseMoved)
	//	//	{
	//	//		if (mouseHidden)
	//	//		{
	//	//			int mx = event.mouseMove.x - w / 2;
	//	//			int my = event.mouseMove.y - h / 2;
	//	//			mouseX += mx;
	//	//			mouseY += my;
	//	//			sf::Mouse::setPosition(sf::Vector2i(w / 2, h / 2), window);

	//	//		}
	//	//	}
	//	//	else if (event.type == sf::Event::MouseButtonPressed)
	//	//	{
	//	//		
	//	//		window.setMouseCursorVisible(false);
	//	//		mouseHidden = true;
	//	//	}
	//	//	else if (event.type == sf::Event::KeyPressed)
	//	//	{
	//	//		if (event.key.code == sf::Keyboard::Escape)
	//	//		{
	//	//			window.setMouseCursorVisible(true);
	//	//			mouseHidden = false;
	//	//		}
	//	//		else if (event.key.code == sf::Keyboard::W) wasdUD[0] = true;
	//	//		else if (event.key.code == sf::Keyboard::A) wasdUD[1] = true;
	//	//		else if (event.key.code == sf::Keyboard::S) wasdUD[2] = true;
	//	//		else if (event.key.code == sf::Keyboard::D) wasdUD[3] = true;
	//	//		else if (event.key.code == sf::Keyboard::Space) wasdUD[4] = true;
	//	//		else if (event.key.code == sf::Keyboard::LShift) wasdUD[5] = true;
	//	//	}
	//	//	else if (event.type == sf::Event::KeyReleased)
	//	//	{
	//	//		if(event.key.code == sf::Keyboard::W) wasdUD[0] = false;
	//	//		else if (event.key.code == sf::Keyboard::A) wasdUD[1] = false;
	//	//		else if (event.key.code == sf::Keyboard::S) wasdUD[2] = false;
	//	//		else if (event.key.code == sf::Keyboard::D) wasdUD[3] = false;
	//	//		else if (event.key.code == sf::Keyboard::Space) wasdUD[4] = false;
	//	//		else if (event.key.code == sf::Keyboard::LShift) wasdUD[5] = false;

	//	//	}
	//	//}
	//	//if (mouseHidden)
	//	//{
	//	//	sf::Vector3f dirTemp;
	//	//	sf::Vector3f dir = sf::Vector3f(0.0f, 0.0f, 0.0f);
	//	//	if(wasdUD[0]) dir = sf::Vector3f(-1.0f, 0.0f, 0.0f);
	//	//	else if (wasdUD[2]) dir = sf::Vector3f(1.0f, 0.0f, 0.0f);
	//	//	if(wasdUD[1]) dir += sf::Vector3f(0.0f, -1.0f, 0.0f);
	//	//	else if (wasdUD[3]) dir += sf::Vector3f(0.0f, 1.0f, 0.0f);


	//	//	float mx = ((float)mouseX / w - 0.5f) * mouseSensitivity;
	//	//	float my = ((float)mouseY / h - 0.5f) * mouseSensitivity;
	//	//	dirTemp.z = dir.z * cos(-my) - dir.x * sin(-my);
	//	//	dirTemp.x = dir.z * sin(-my) - dir.x * cos(-my);
	//	//	dirTemp.y = dir.y;
	//	//	dir.x = dirTemp.x * cos(mx) - dirTemp.y * sin(mx);
	//	//	dir.y = dirTemp.x * sin(mx) + dirTemp.y * cos(mx);
	//	//	dir.z = dirTemp.z;
	//	//	pos += dir * speed;
	//	//	if (wasdUD[4]) pos.z -= 0.1;
	//	//	else if (wasdUD[5]) pos.z += 0.1;
	//	//	shader.setUniform("u_pos", pos);
	//	//	shader.setUniform("u_mouse",sf::Vector2f(mx,my));
	//	//	window.draw(emptySprite,&shader);
	//	//	
	//	//}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//	{
	//		pl.dx = 0.5;
	//	}
	//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	{
	//		pl.dx = -0.5;
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//	{
	//		if(pl.onGround)
	//			pl.dy =-2.5;
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	{
	//		if (mouseX < (Width - 32) * 32)
	//			mouseX += 64;
	//		view.setCenter(mouseX, mouseY);
	//	}
	//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	{
	//		if (mouseX > 32 * 32)
	//			mouseX -= 64;
	//		view.setCenter(mouseX, mouseY);

	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	{
	//		mouseY -= 64;
	//		view.setCenter(mouseX, mouseY);

	//	}
	//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	{
	//		mouseY += 64;
	//		view.setCenter(mouseX, mouseY);

	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	//		window.close();
	//	for (int i = 0; i < Height; i++)
	//		for (int j = mouseX / 32 - 32; j < mouseX / 32 + 32; j++)
	//		{
	//			if (location.TileMap[i][j] == 1)
	//				rectangle.setFillColor(sf::Color::Black);
	//			if (location.TileMap[i][j] == 0)
	//				rectangle.setFillColor(sf::Color::White);
	//			rectangle.setPosition(j * 32, i * 32);
	//			window.draw(rectangle);
	//		}
	//	pl.update(1);
	//	window.draw(pl.rectangle);
	//	window.display();
	//	window.setView(view);
	//	window.clear(sf::Color::White);
	//}

	return 0;
}
